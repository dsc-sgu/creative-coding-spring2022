#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <iostream>
#include <stdint.h>
#include <cmath>
#include <string>
#include <complex>
#include <vector>

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

int
main(void)
{
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width, screen_height, "Creative Coding: Mandelbrot Set");
    SetTargetFPS(60);

    context_t context = {
        { screen_width, screen_height }, // screen_size
        // Bottom and top are swapped for natural Y axis direction
        { -2, 0.5, 1, -1 }, // viewport
        100, // max_iterations
        std::vector(screen_width, std::vector<pixel_data_t>(screen_height)),
    };

    for (long double x = 0; x < context.screen_size.x; x += 1)
    {
        for (long double y = 0; y < context.screen_size.y; y += 1)
        {
            v2d point = screen_to_local(&context, v2d { x, y });
            context.pixel_data[x][y] = pixel_data_t {
                { 0, 0 }, // z
                { point.x, point.y }, // c
                0, // iteration
                BLACK, // color
                false, // done
            };
        }
    }

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

            for (int x = 0; x < screen_width; ++x)
            {
                for (int y = 0; y < screen_height; ++y)
                {
                    pixel_data_t *pixel = &context.pixel_data[x][y];
                    iterate(&context, pixel);
                    DrawPixel(x, y, pixel->color);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
