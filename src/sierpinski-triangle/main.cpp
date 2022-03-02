#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <vector>

int main()
{
    const int WINDOW_W = 600;
    const int WINDOW_H = 600;

    InitWindow(WINDOW_W, WINDOW_H, "Creative Coding: Sierpinski Triangle");
    SetTargetFPS(60);

    // Set position of triangle vertices
    const int PADDING = 50;
    Vector2 triangle[] = {
        {WINDOW_W / 2, PADDING},
        {PADDING, WINDOW_H - PADDING},
        {WINDOW_W - PADDING, WINDOW_H - PADDING}
    };

    std::vector<Vector2> points;
    points.push_back(triangle[0]);

    int iteration = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(BLACK);
            // Draw triangle vertices
            for (int i = 0; i < 3; ++i)
                DrawCircleV(triangle[i], 5, GREEN);
            // Draw all generated points
            for (auto point : points)
                DrawPixelV(point, GREEN);
            // Draw text with iteration number
            DrawText("Iteration: " + std::to_string(iteration), 20, 20, 20,
                     GRAY);
            ++iteration;
            // Generate next point based on previous:
            // Move towards random vertex by half distance
            points.push_back((*points.rbegin() + triangle[rand() % 3]) / 2);
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
