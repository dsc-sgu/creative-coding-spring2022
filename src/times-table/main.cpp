#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <cmath>

int main()
{
    const int screen_radius = 350;
    const int screen_width = screen_radius * 2;
    const int screen_height = screen_radius * 2;

    InitWindow(screen_width, screen_height, "Creative Coding: Times Table");
    SetTargetFPS(60);

    const int lines_count = 200;
    const int radius = screen_radius - 10;
    const Vector2 center = { screen_radius, screen_radius };
    const float step = 0.01f;
    const float theta = 2.0 * PI / lines_count;

    float multiple = 1.0f;
    float hue = 0;

    while (!WindowShouldClose())
    {
        multiple += step;

        BeginDrawing();
        {
            ClearBackground(BLACK);

            Color line_color = ColorFromHSV(hue, 1, 1);
    
            DrawRing(
                center, radius + 1, radius + 3,
                0, 360, 200, line_color
            );

            for (int n = 0; n < lines_count; ++n)
            {
                Vector2 start = Vector2 {
                    cosf(theta * n),
                    sinf(theta * n)
                } * radius + center;

                Vector2 end = Vector2 {
                    cosf(theta * multiple * n),
                    sinf(theta * multiple * n)
                } * radius + center;

                DrawLineV(start, end, line_color);
            }

            hue += 0.5;
            if (hue > 360) hue = 0;
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
