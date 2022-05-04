#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <algorithm>
#include <vector>

const int screenWidth = 640;
const int screenHeight = 640;

const int board_w = 8;
const int board_h = 8;

const int cell_size = screenWidth / board_w;

int board[board_w][board_h] = {
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 2, 0, 0, 0, 1, 1 },
    { 1, 2, 2, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
};

Image floor_texture = LoadImage("./textures/FLOOR_1A.png");
Image ceiling_texture = LoadImage("./textures/LIGHT_1C.png");
Image images[] = {
    LoadImage("./textures/TECH_1A.png"), // NULL
    LoadImage("./textures/TECH_1A.png"),
    LoadImage("./textures/SUPPORT_3.png"),
};

struct player_t {
    Vector2 pos;
    float rotation;
    float speed;
    float fov;
    int rays_count;
};

struct hit_t {
    Vector2 pos;
    struct { int x, y; } cell_pos;
    bool is_horizontal;
    float angle;
};

bool correct_cell(int x, int y)
{
    return (x >= 0 && x < board_w) && (y >= 0 && y < board_h);
}

float
fix_angle(float angle)
{
    while (angle > PI)  angle -= 2 * PI;
    while (angle < -PI) angle += 2 * PI;
    return angle;
}

hit_t cast_ray(Vector2 pos, float dir)
{
    dir = fix_angle(dir);

    int cell_x = pos.x / cell_size;
    int cell_y = pos.y / cell_size;

    hit_t hit_data_v, hit_data_h;

    // Vertical hit
    for (int k = 0; ; ++k) {
        int shift;
        int k_dir;
        if (dir > -PI / 2 && dir < PI / 2) {
            shift = 1;
            k_dir = 1;
        }
        else {
            shift = 0;
            k_dir = -1;
        }

        float dx = (cell_x + shift + k * k_dir) * cell_size - pos.x;
        float dy = dx * tan(dir);
        Vector2 d = { dx, dy };
        Vector2 hit = d + pos;

        int cell_hit_x = int(hit.x / cell_size) + shift - 1;
        int cell_hit_y = int(hit.y / cell_size);

        hit_data_v.pos = hit;
        hit_data_v.cell_pos = { cell_hit_x, cell_hit_y };
        hit_data_v.is_horizontal = false;
        hit_data_v.angle = dir;

        if (!correct_cell(cell_hit_x, cell_hit_y))
            break;
        if (board[cell_hit_x][cell_hit_y] != 0)
            break;
    }

    // Horizontal hit
    for (int k = 0; ; ++k) {
        int shift;
        int k_dir;
        if (dir > -PI && dir < 0) {
            shift = 0;
            k_dir = -1;
        }
        else {
            shift = 1;
            k_dir = 1;
        }

        float dy = (cell_y + shift + k * k_dir) * cell_size - pos.y;
        float dx = dy / tan(dir);
        Vector2 d = { dx, dy };
        Vector2 hit = d + pos;

        int cell_hit_x = int(hit.x / cell_size);
        int cell_hit_y = int(hit.y / cell_size) + shift - 1;

        hit_data_h.pos = hit;
        hit_data_h.cell_pos = { cell_hit_x, cell_hit_y };
        hit_data_h.is_horizontal = true;
        hit_data_h.angle = dir;

        if (!correct_cell(cell_hit_x, cell_hit_y))
            break;
        if (board[cell_hit_x][cell_hit_y] != 0)
            break;
    }

    if (Vector2Length(hit_data_h.pos - pos) < Vector2Length(hit_data_v.pos - pos)) {
        return hit_data_h;
    }
    else {
        return hit_data_v;
    }
}

bool
check_collision(Vector2 position, float radius)
{
    for (float angle = -PI; angle < PI; angle += PI / 4)
    {
        Vector2 check = position + Vector2Rotate({ radius, 0 }, angle);
        int cell_x = check.x / cell_size;
        int cell_y = check.y / cell_size;
        if (board[cell_x][cell_y] != 0)
            return true;
    }
    return false;
}

int main()
{
    InitWindow(screenWidth * 2, screenHeight, "GDSC: Creative Coding");
    SetTargetFPS(60);

    player_t player;
    player.pos = { screenWidth / 2, screenHeight / 2 };
    player.speed = 100;
    player.rotation = 0;
    player.fov = 60;
    player.rays_count = 240;
    float delta_angle = player.fov / player.rays_count;

    bool mouse_2d = false;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        Vector2 move = { 0, 0 };
        if (mouse_2d)
        {
            if (IsKeyDown(KEY_W))
                move.y -= player.speed * dt;
            if (IsKeyDown(KEY_S))
                move.y += player.speed * dt;
            if (IsKeyDown(KEY_A))
                move.x -= player.speed * dt;
            if (IsKeyDown(KEY_D))
                move.x += player.speed * dt;

            Vector2 mp = {
                GetMouseX() - player.pos.x,
                GetMouseY() - player.pos.y
            };
            player.rotation = Vector2Angle({ 1, 0 }, mp);
        }
        else
        {
            DisableCursor();
            float delta = GetMouseDelta().x;
            player.rotation += delta * dt * 0.1;
            Vector2 dir = Vector2Rotate({ 1, 0 }, player.rotation);
            Vector2 forward = dir * (player.speed * dt);
            Vector2 right = Vector2Rotate(forward, PI / 2);
            if (IsKeyDown(KEY_W))
                move = forward;
            if (IsKeyDown(KEY_S))
                move = -forward;
            if (IsKeyDown(KEY_A))
                move = -right;
            if (IsKeyDown(KEY_D))
                move = right;
        }
        player.pos += move;
        if (check_collision(player.pos, 15))
            player.pos -= move;


        BeginDrawing();
        {
            ClearBackground(BLACK);
            
            DrawRectangle(screenWidth, screenHeight / 2, screenWidth, screenHeight / 2, BLACK);

            for (int row = 0; row < board_h; ++row) {
                for (int col = 0; col < board_w; ++col) {
                    if (board[col][row] != 0) {
                        DrawRectangle(col * cell_size, row * cell_size,
                            cell_size, cell_size, BLACK);
                    }
                    else
                    {
                        DrawRectangle(col * cell_size, row * cell_size,
                            cell_size, cell_size, WHITE);
                    }
                }
            }

            for (int x = cell_size; x < screenWidth; x += cell_size) {
                DrawLine(x, 0, x, screenHeight, GRAY);
            }
            for (int y = cell_size; y < screenHeight; y += cell_size) {
                DrawLine(0, y, screenWidth, y, GRAY);
            }

            DrawCircleV(player.pos, 14, RED);

            DrawLineEx(player.pos, player.pos + Vector2Rotate({ 1,0 }, player.rotation) * 25, 5, BLUE);

            std::vector<hit_t> hits;
            for (float angle = -player.fov / 2; angle < player.fov / 2; angle += delta_angle) {
                hit_t hit = cast_ray(player.pos, player.rotation + angle * DEG2RAD);
                DrawLineEx(player.pos, hit.pos, 2, BLUE);
                hits.push_back(hit);
            }

            float rect_x = 0;
            for (hit_t& hit : hits)
            {
                Vector2 hit_delta = hit.pos - player.pos;
                float dist = hit_delta.x * cos(player.rotation) +
                    hit_delta.y * sin(player.rotation);

                int shading = int(128.0 * dist / 900);

                float rect_h = (cell_size * screenHeight) / dist;
                float rect_w = (screenWidth / player.fov) * delta_angle;
                float rect_y = (screenHeight - rect_h) / 2;

                int image_idx = board[hit.cell_pos.x][hit.cell_pos.y];
                Image cell_image = images[image_idx];

                Vector2 pos_in_cell = {
                    hit.pos.x - hit.cell_pos.x * cell_size,
                    hit.pos.y - hit.cell_pos.y * cell_size,
                };

                Vector2 column = pos_in_cell / cell_size * cell_image.width;
                int col = column.y;
                if (hit.is_horizontal)
                    col = column.x;
                
                for (int i = 0; i < cell_image.height; ++i)
                {
                    Color* color_data = (Color*)cell_image.data;
                    Color pixel = color_data[i * cell_image.width + col];
                    pixel.r = std::clamp(pixel.r - shading, 0, 255);
                    pixel.g = std::clamp(pixel.g - shading, 0, 255);
                    pixel.b = std::clamp(pixel.b - shading, 0, 255);

                    DrawRectangle(
                        screenWidth + rect_x, rect_y + rect_h / cell_image.height * i,
                        rect_w + 1, rect_h / cell_image.height + 1, pixel
                    );
                }

                for (int row = rect_y + rect_h; row < screenHeight; ++row)
                {
                    float dy = row - screenHeight / 2;
                    float raFix = cosf(fix_angle(player.rotation - hit.angle));
                    int magic = 200;
                    int tx = player.pos.x / 2 + cosf(hit.angle) * magic * floor_texture.width / dy / raFix;
                    int ty = player.pos.y / 2 + sinf(hit.angle) * magic * floor_texture.height / dy / raFix;

                    shading = int(1.0 / float(row) * screenHeight * 28);

                    int fw = floor_texture.width;
                    Color* floor_data = (Color*)floor_texture.data;
                    Color floor_pixel = floor_data[(ty & (fw - 1)) * fw + (tx & (fw - 1))];
                    floor_pixel.r = std::clamp(floor_pixel.r - shading, 0, 255);
                    floor_pixel.g = std::clamp(floor_pixel.g - shading, 0, 255);
                    floor_pixel.b = std::clamp(floor_pixel.b - shading, 0, 255);
                    DrawRectangle(
                        screenWidth + rect_x, row + rect_h / floor_texture.height,
                        rect_w + 1, rect_h / floor_texture.height + 1, floor_pixel
                    );

                    int cw = ceiling_texture.width;
                    Color* ceiling_data = (Color*)ceiling_texture.data;
                    Color ceiling_pixel = ceiling_data[(ty & (cw - 1)) * cw + (tx & (cw - 1))];
                    ceiling_pixel.r = std::clamp(ceiling_pixel.r - shading, 0, 255);
                    ceiling_pixel.g = std::clamp(ceiling_pixel.g - shading, 0, 255);
                    ceiling_pixel.b = std::clamp(ceiling_pixel.b - shading, 0, 255);
                    DrawRectangle(
                        screenWidth + rect_x, screenHeight - row - rect_h / ceiling_texture.height,
                        rect_w + 1, rect_h / ceiling_texture.height + 1, ceiling_pixel
                    );
                }

                rect_x += rect_w;
            }
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
