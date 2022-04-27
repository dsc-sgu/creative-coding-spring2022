#define RAYEXT_IMPLEMENTATION
#include <raylib-ext.hpp>
#include <cmath>
#include <map>
#include <stack>

struct State {
    Vector2 pos;
    float angle;
};

struct Turtle {
    Vector2 pos;
    float angle;
    Color color;
    float thickness;

    Turtle(Vector2 pos, float angle, float thickness, Color color) :
        pos(pos), angle(angle * DEG2RAD), thickness(thickness), color(color) {}

    void forward(float length)
    {
        Vector2 new_pos = pos + Vector2 { cosf(-angle), sin(-angle) } * length;
        DrawLineEx(pos, new_pos, thickness, color);
        pos = new_pos;
    }

    void rotate(float a)
    {
        angle += a * DEG2RAD;
    }

    void set_pos(Vector2 pos, float angle)
    {
        this->pos = pos;
        this->angle = angle * DEG2RAD;
    }
};

uint8_t coloring(double x, double q, double p)
{
    double a = cos(sqrt(x) * q + p);
    return uint8_t(255.0 * a * a);
}

int main()
{
    const int screenWidth  = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Creative Coding: L-systems");
    SetTargetFPS(24);

    Turtle turtle(Vector2 {screenWidth / 2., screenHeight / 2.}, 90, 2, GREEN);

    std::stack<State> states;
    std::string axiom = "F";
    std::map<char, std::string> rules = {
        {'F', "FF-[-F+F+F]+[+F-F-F]"},
        {'+', "+"},
        {'-', "-"},
        {']', "]"},
        {'[', "["},
    };
    unsigned iteration = 4;
    float shift_angle = 15;
    float shift_len = 12;

    for (int i = 0; i < iteration; ++i) {
        std::string new_axiom = "";
        for (int j = 0; j < axiom.length(); ++j) {
            new_axiom += rules[axiom[j]];
        }
        axiom = new_axiom;
    }

    while (!WindowShouldClose())
    {
        turtle.set_pos(Vector2 {screenWidth / 2., screenHeight}, 90);
        float x;
        BeginDrawing();
        {
            ClearBackground(BLACK);
            for (int j = 0; j < axiom.length(); ++j) {
                switch (axiom[j])
                {
                case 'F':
                    turtle.color = Color {
                        coloring(j, 1, 0),
                        coloring(j, 1, 120),
                        coloring(j, 1, 240),
                        255
                    };
                    turtle.forward(shift_len);
                    break;
                case '+':
                    turtle.rotate(shift_angle);
                    break;
                case '-':
                    turtle.rotate(-shift_angle);
                    break;
                case '[':
                    states.push(State {turtle.pos, turtle.angle});
                    break;
                case ']':
                    turtle.pos = states.top().pos;
                    turtle.angle = states.top().angle;
                    states.pop();
                    break;
                default:
                    break;
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
