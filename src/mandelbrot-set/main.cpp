#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <iostream>
#include <stdint.h>
#include <cmath>
#include <string>
#include <complex>
#include <vector>
#include <thread>

struct v2d
{
    long double x, y;
};

struct viewport_t
{
    long double left, right;
    long double bottom, top;
};

struct pixel_data_t
{
    std::complex<long double> z;
    std::complex<long double> c;
    int iteration;
    Color color;
    bool done;
};

struct context_t
{
    Vector2 screen_size;
    viewport_t viewport;
    int max_iterations;
    std::vector<std::vector<pixel_data_t>> pixel_data;
};

v2d
screen_to_local(context_t *ctx, v2d point)
{
    v2d d = {
        ctx->viewport.right - ctx->viewport.left,
        ctx->viewport.top - ctx->viewport.bottom
    };
    return v2d {
        (point.x / ctx->screen_size.x) * d.x + ctx->viewport.left,
        (point.y / ctx->screen_size.y) * d.y + ctx->viewport.bottom,
    };
}

uint8_t
f(double x, double q, double p)
{
    double a = cos(sqrt(x) * q + p);
    return uint8_t(255.0 * a * a);
}

void
iterate(context_t *ctx, pixel_data_t *pixel_data)
{
    if (pixel_data->done) return;

    auto z = pixel_data->z;
    auto c = pixel_data->c;
    pixel_data->z = z * z + c;
    pixel_data->iteration++;

    if (std::abs(z) > 2)
    {
        int i = pixel_data->iteration;
        pixel_data->color = Color { 
            f(i, 1, 0), f(i, 1, 120), f(i, 1, 240), 255
        };
        pixel_data->done = true;
    }
    if (pixel_data->iteration >= ctx->max_iterations)
        pixel_data->done = true;
}

Rectangle
fix_rect(Rectangle rect)
{
    Rectangle fixed = rect;
    if (fixed.width < 0)
    {
        fixed.x += fixed.width;
        fixed.width *= -1;
    }
    if (fixed.height < 0)
    {
        fixed.y += fixed.height;
        fixed.height *= -1;
    }
    return fixed;
}

void
worker(context_t *context, const int offset, const int width, const int screen_height)
{
    for (int x = offset; x < offset + width; ++x)
    {
        for (int y = 0; y < screen_height; ++y)
        {
            pixel_data_t *pixel = &context->pixel_data[x][y];
            iterate(context, pixel);
        }
    } 
}

void
set_viewport(context_t *context, Rectangle rect)
{
    v2d p0 = screen_to_local(context, v2d { rect.x, rect.y });
    v2d p1 = screen_to_local(context, v2d { rect.x + rect.width, rect.y + rect.height });
    context->viewport = viewport_t {
        p0.x,
        p1.x,
        p0.y,
        p1.y,
    };

    for (long double x = 0; x < context->screen_size.x; x += 1)
    {
        for (long double y = 0; y < context->screen_size.y; y += 1)
        {
            v2d point = screen_to_local(context, v2d { x, y });
            context->pixel_data[x][y] = pixel_data_t {
                { 0, 0 }, // z
                { point.x, point.y }, // c
                0, // iteration
                BLACK, // color
                false, // done
            };
        }
    }
}

int
main(void)
{
    const int screen_width = 800;
    const int screen_height = 600;
    const float aspect = screen_width * 1.0 / screen_height;

    InitWindow(screen_width, screen_height, "Creative Coding: Mandelbrot Set");
    SetTargetFPS(60);

    context_t context = {
        { screen_width, screen_height }, // screen_size
        // Bottom and top are swapped for natural Y axis direction
        { -2, 0.5, 1.12, -1.12 }, // viewport
        100, // max_iterations
        std::vector(screen_width, std::vector<pixel_data_t>(screen_height)),
    };

    set_viewport(&context, { 0, 0, screen_width, screen_height });

    Rectangle selected_rect = { 0, 0, 0, 0 };
    bool selecting = false;
    while (!WindowShouldClose())
    {
        float deltatime = GetFrameTime();
        char title[128];
        sprintf(
            title, "Creative Coding: Mandelbrot Set [fps = %f]",
            1 / deltatime
        );
        SetWindowTitle(title);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            const int ncpu = std::thread::hardware_concurrency();
            const int column_width = screen_width / ncpu;

            std::vector<std::thread> threads(ncpu);
            for (int i = 0; i < ncpu; ++i)
            {
                threads[i] = std::thread(&worker, &context, 
                    i * column_width, column_width, screen_height);
            }

            for (int i = 0; i < ncpu; ++i)
            {
                threads[i].join();
            }            

            for (int x = 0; x < screen_width; ++x)
            {
                for (int y = 0; y < screen_height; ++y)
                {
                    pixel_data_t *pixel = &context.pixel_data[x][y];
                    DrawPixel(x, y, pixel->color);
                }
            }

            if (selecting)
            {
                Rectangle fixed = fix_rect(selected_rect);
                DrawRectangleRec(fixed, { 255, 255, 255, 50 });
                DrawRectangleLinesEx(fixed, 1, WHITE);
            }
                
        }
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE))
        {
            context.viewport = { -2, 0.5, 1.12, -1.12 };
            context.max_iterations = 100;
            set_viewport(&context, { 0, 0, screen_width, screen_height });
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            selected_rect.x = float(GetMouseX());
            selected_rect.y = float(GetMouseY());
            selecting = true;

        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            selected_rect.width =  float(GetMouseX()) - selected_rect.x;
            selected_rect.height = float(GetMouseY()) - selected_rect.y;
            selected_rect.height = copysign(selected_rect.width / aspect, selected_rect.height);
        }

        if (selecting && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            float area = std::abs(selected_rect.width * selected_rect.height);
            context.max_iterations *= sqrt(sqrt(log(area)));
            set_viewport(&context, fix_rect(selected_rect));
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            selected_rect = { 0, 0, 0, 0 };
            selecting = false;
        }
    }

    CloseWindow();

    return 0;
}
