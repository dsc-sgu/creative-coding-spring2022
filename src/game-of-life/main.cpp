#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>

const Color BG_COLOR = BLACK;
const Color ACTIVE_COLOR = GREEN;
const Color BORDER_COLOR = DARKGRAY;

const int WINDOW_W = 800;
const int WINDOW_H = 800;

const int SQUARE_SIZE = 20;
const int BOARD_W = WINDOW_W / SQUARE_SIZE;
const int BOARD_H = WINDOW_H / SQUARE_SIZE;
bool board[BOARD_H][BOARD_W] = {0};

bool is_valid(int x, int y)
{
    return ((x >= 0 && x < BOARD_W) && (y >= 0 && y < BOARD_H));
}

void update_board()
{
    bool buf[BOARD_H][BOARD_W] = {0};
    for (int sy = 0; sy < BOARD_H; ++sy) {
        for (int sx = 0; sx < BOARD_W; ++sx) {
            // Count alive cells around
            int alive = 0;
            for (int i = 0; i < 9; ++i) {
                int x = sx - 1 + i % 3;
                int y = sy - 1 + i / 3;
                if (is_valid(x, y) && (x != sx || y != sy))
                    alive += board[y][x];
            }
            // Update current cell based on its neighbors
            if (board[sy][sx])
                buf[sy][sx] = (alive == 2 || alive == 3);
            else
                buf[sy][sx] = (alive == 3);
        }
    }
    // Save new generation to the board
    memcpy(board, buf, sizeof(buf));
}

int main()
{
    InitWindow(WINDOW_W, WINDOW_H, "Creative Coding: Game of Life");
    SetTargetFPS(60);

    // Game state
    bool is_running = false;
    float timeout = 0;

    while (!WindowShouldClose()) {
        // Draw on the board
        if (!is_running) {
            int sx = GetMouseX() / SQUARE_SIZE;
            int sy = GetMouseY() / SQUARE_SIZE;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                board[sy][sx] = 1;
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                board[sy][sx] = 0;
        }

        // Change game state
        if (IsKeyPressed(KEY_SPACE))
            is_running = !is_running;

        BeginDrawing();
        {
            ClearBackground(BG_COLOR);
            // Draw squares
            for (int sy = 0; sy < BOARD_H; ++sy)
                for (int sx = 0; sx < BOARD_W; ++sx)
                    if (board[sy][sx])
                        DrawRectangle(sx * SQUARE_SIZE, sy * SQUARE_SIZE,
                                    SQUARE_SIZE, SQUARE_SIZE, ACTIVE_COLOR);
            // Draw horizontal lines
            for (int y = 0; y <= WINDOW_H; y += SQUARE_SIZE)
                DrawLine(0, y, WINDOW_W, y, BORDER_COLOR);
            // Draw vertical lines
            for (int x = 0; x <= WINDOW_W; x += SQUARE_SIZE)
                DrawLine(x, 0, x, WINDOW_H, BORDER_COLOR);
        }
        EndDrawing();

        // Update frame only after timeout
        if (timeout <= 0) {
            timeout = 0.1;
        } else {
            timeout -= GetFrameTime();
            continue;
        }

        if (is_running)
            update_board();
    }
    CloseWindow();

    return 0;
}
