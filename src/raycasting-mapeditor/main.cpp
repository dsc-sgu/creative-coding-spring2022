#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

#define SCALE_DELTA 0.3

const Color BG_COLOR = BLACK;
const Color ACTIVE_COLOR = GREEN;
const Color BORDER_COLOR = DARKGRAY;

struct context_t
{
    Vector2 offset;
    struct { int rows, cols; } board_size;
    float base_cell_size;
    float scale;
    // int *board;
    std::vector<std::vector<int>> board;
    int images_loaded;
    std::vector<Image> images_base;
    std::vector<Image> images_resized;
    std::vector<bool> needs_resizing;
    std::vector<Texture> textures;
    std::vector<std::string> filenames;

    Texture gui_current_tecture;
    bool gui_enabled;

    void
    reload_board()
    {
        auto new_board = std::vector(this->board_size.rows, std::vector(this->board_size.cols, -1));
        int max_row = std::min(int(this->board.size()), this->board_size.rows);
        int max_col = std::min(int(this->board[0].size()), this->board_size.cols);
        for (int i = 0; i < max_row; ++i)
            for (int j = 0; j < max_col; ++j)
            {
                new_board[i][j] = this->board[i][j];
            }

        this->board = new_board;
    }

    std::string
    get_map_data()
    {
        std::string data = "";
        data.append(std::to_string(this->board_size.rows)).append(" ");
        data.append(std::to_string(this->board_size.cols)).append(" ");

        std::vector<bool> used(this->images_loaded, false);
        int count = 0;
        std::string board_string = "";
        for (int i = 0; i < int(this->board.size()); ++i)
        {
            for (int j = 0; j < int(this->board[i].size()); ++j)
            {
                int cell = this->board[i][j];
                if (cell != -1 && !used[cell])
                {
                    used[cell] = true;
                    count++;
                }
                board_string.append(std::to_string(cell));
                if (j == int(this->board[i].size()) - 1)
                    board_string.append("\n");
                else
                    board_string.append(" ");
            }
        }
        data.append(std::to_string(count)).append("\n");
        for (int i = 0; i < used.size(); ++i)
            if (used[i])
            {
                data.append(std::to_string(i)).append(" ");
                data.append(this->filenames[i]).append("\n");
            }
        data.append(board_string);

        return data;
    }
};

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "GDSC: Creative Coding");
    SetTargetFPS(60);

    context_t context;
    context.offset = {0, 0};
    context.board_size = {10, 10};
    context.base_cell_size = 40;
    context.scale = 1;
    context.board = std::vector(context.board_size.rows, std::vector(context.board_size.cols, -1));

    context.board[0][0] = 0;
    context.board[1][0] = 0;
    context.images_loaded = 0;
    context.images_base = std::vector<Image>();

    std::string path = "./resources";
    for (const auto &entry : fs::directory_iterator(path))
    {
        Image texture = LoadImage(entry.path());
        context.images_base.push_back(texture);
        context.filenames.push_back(entry.path());
        context.images_loaded++;
    }
    context.images_resized = std::vector<Image>(context.images_loaded);
    context.needs_resizing = std::vector<bool>(context.images_loaded, true);
    context.textures = std::vector<Texture>(context.images_loaded);
    context.gui_enabled = false;

    int listViewActive = -1;
    int listViewScrollIndex = 0;

    bool spinner_rows_edit = false;
    bool spinner_cols_edit = false;

    char filename_text[32] = "./test.map";
    bool filename_edit = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            if (!context.gui_enabled && IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
            {
                Vector2 md = GetMouseDelta();
                context.offset += md;
            }

            if (!context.gui_enabled && IsKeyPressed(KEY_EQUAL))
            {
                context.scale += SCALE_DELTA;
                for (int i = 0; i < context.images_loaded; ++i)
                    context.needs_resizing[i] = true;
            }
            else if (!context.gui_enabled && IsKeyPressed(KEY_MINUS))
            {
                if (context.scale - SCALE_DELTA > 0.3)
                {
                    context.scale -= SCALE_DELTA;
                    for (int i = 0; i < context.images_loaded; ++i)
                        context.needs_resizing[i] = true;
                }
            }

            float sq = context.base_cell_size * context.scale;
            Vector2 sq_dim = { sq, sq };

            if (!context.gui_enabled && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                Vector2 mp = { float(GetMouseX()), float(GetMouseY()) };
                mp -= context.offset;
                int cell_row = mp.y / sq;
                int cell_col = mp.x / sq;
                if (cell_row >= 0 && cell_row < context.board_size.rows &&
                    cell_col >= 0 && cell_col < context.board_size.cols)
                {
                    context.board[cell_row][cell_col] = listViewActive;
                }
            }

            ClearBackground(BLACK);

            // Draw map 
            for (int col = 0; col < context.board_size.cols; ++col)
                for (int row = 0; row < context.board_size.rows; ++row)
                    if (context.board[row][col] != -1)
                    {
                        Vector2 pos = { float(col), float(row) };
                        pos = pos * sq + context.offset;
                        int cell = context.board[row][col];
                        Texture texture;
                        if (context.needs_resizing[cell])
                        {
                            UnloadTexture(context.textures[cell]);
                            Image *resized = &context.images_resized[cell];
                            *resized = ImageCopy(context.images_base[cell]);
                            ImageResize(resized, sq, sq);
                            context.textures[cell] = LoadTextureFromImage(*resized);
                            texture = context.textures[cell];
                            context.needs_resizing[cell] = false;
                        }
                        else
                        {
                            texture = context.textures[cell];
                        }
                        DrawTextureV(texture, pos, WHITE);
                    }

            // Draw horizontal lines
            for (int col = 0; col <= context.board_size.cols; ++col)
            {
                Vector2 p0 = { 0, col * sq };
                Vector2 p1 = { context.board_size.rows * sq, col * sq };
                DrawLineV(p0 + context.offset, p1 + context.offset, BORDER_COLOR);
            }
            for (float x = 0; x <= screenWidth; x += sq)
            for (int row = 0; row <= context.board_size.rows; ++row)
            {
                Vector2 p0 = { row * sq, 0 };
                Vector2 p1 = { row * sq, context.board_size.cols * sq };
                DrawLineV(p0 + context.offset, p1 + context.offset, BORDER_COLOR);
            }
        }
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                context.gui_enabled = !context.gui_enabled;
            }

            if (context.gui_enabled) 
            {
                DrawRectangleRec(Rectangle { 10, 10, 125, 30 }, WHITE);
                auto old_size = context.board_size;
                if (GuiSpinner(
                    (Rectangle){ 10, 10, 125, 30 },
                    NULL, &context.board_size.rows, 
                    1, 100, spinner_rows_edit))
                {
                    spinner_rows_edit = !spinner_rows_edit;
                }
                DrawRectangleRec(Rectangle { 145, 10, 125, 30 }, WHITE);
                if (GuiSpinner(
                    (Rectangle){ 145, 10, 125, 30 },
                    NULL, &context.board_size.cols,
                    1, 100, spinner_cols_edit))
                {
                    spinner_cols_edit = !spinner_cols_edit;
                }

                if (old_size.rows != context.board_size.rows ||
                    old_size.cols != context.board_size.cols)
                {
                    context.reload_board();
                }

                DrawRectangleRec(Rectangle { 280, 10, 125, 30 }, WHITE);
                if (GuiTextBox(
                    (Rectangle){ 280, 10, 125, 30 },
                    filename_text, 32, filename_edit))
                {
                    filename_edit = !filename_edit;
                }

                if (GuiButton(Rectangle { 415, 10, 125, 30 }, "Export Map"))
                {
                    std::ofstream map_file;
                    map_file.open (filename_text);
                    map_file << context.get_map_data();
                    map_file.close();
                }

                std::string menu = "";
                for (int i = 0; i < context.images_loaded; ++i)
                {
                    menu.append(context.filenames[i]);
                    if (i != context.images_loaded)
                        menu.append(";");
                }
                int prev_listViewActive = listViewActive;
                listViewActive = GuiListView(
                    (Rectangle){ 10, 50, 200, screenHeight - 60 },
                    menu.c_str(),
                    &listViewScrollIndex,
                    listViewActive
                );

                if (prev_listViewActive != listViewActive)
                {
                    UnloadTexture(context.gui_current_tecture);
                    Image image = ImageCopy(context.images_base[listViewActive]);
                    ImageResize(&image, 400, 400);
                    context.gui_current_tecture = LoadTextureFromImage(image);
                }
                if (listViewActive != -1)
                {
                    DrawRectangle(
                        10 + 200 + (screenWidth - 210) / 2 - 200 - 2,
                        40 + (screenHeight - 40) / 2 - 200 - 2,
                        404, 404, WHITE
                    );
                    DrawTexture(
                        context.gui_current_tecture,
                        10 + 200 + (screenWidth - 210) / 2 - 200, 
                        40 + (screenHeight - 40) / 2 - 200,
                        WHITE
                    );
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
