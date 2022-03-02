#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "GDSC: Creative Coding");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(BLACK);
            int fontSize = 30;
            std::string msg = "Welcome, Creative Coders!";
            int x = (screenWidth - MeasureText(msg, fontSize)) / 2;
            int y = (screenHeight - fontSize) / 2;
            DrawText(msg, x, y, fontSize, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
