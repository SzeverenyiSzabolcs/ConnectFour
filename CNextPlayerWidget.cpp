#include "CNextPlayerWidget.hpp"
#include "CGameMaster.hpp"
#include "graphics.hpp"
#include <cmath>
#include <string>

using namespace genv;

namespace
{
    void draw_filled_circle(int cx, int cy, int radius, int red, int green, int blue)
    {
        for (int dy = -radius; dy <= radius; ++dy)
        {
            int span = radius * radius - dy * dy;
            int dx_max = static_cast<int>(std::sqrt(static_cast<double>(span)));
            for (int dx = -dx_max; dx <= dx_max; ++dx)
            {
                gout.dot(cx + dx, cy + dy, red, green, blue);
            }
        }
    }
}

CNextPlayerWidget::CNextPlayerWidget(int x_, int y_, int w_, int h_, CGameMaster* game_)
    : CWidget(x_, y_, w_, h_), game(game_)
{
}

void CNextPlayerWidget::Draw() const
{
    gout << color(255, 255, 255)
         << move_to(x, y)
         << box(w, h);

    gout << color(30, 30, 30)
         << move_to(x, y)
         << line(w, 0)
         << line(0, h)
         << line(-w, 0)
         << line(0, -h);

    std::string title = "Következő";
    if (game->GetWinner() == 1 || game->GetWinner() == 2)
    {
        title = "Nyertes";
    }
    else if (game->IsDraw())
    {
        title = "Döntetlen";
    }

    int tx = x + (w - gout.twidth(title)) / 2;
    int ty = y + 30;

    gout << move_to(tx, ty)
         << text(title);

    int red = 210;
    int green = 210;
    int blue = 210;

    if (game->IsDraw())
    {
        red = 210;
        green = 210;
        blue = 210;
    }
    else
    {
        int player = game->GetWinner() != 0 ? game->GetWinner() : game->GetCurrentPlayer();
        if (player == 1)
        {
            red = 220;
            green = 40;
            blue = 40;
        }
        else
        {
            red = 240;
            green = 220;
            blue = 40;
        }
    }

    int cx = x + w / 2;
    int cy = y + h / 2 + 15;
    int radius = 42;

    draw_filled_circle(cx, cy, radius, red, green, blue);

    gout << color(70, 70, 70)
         << move_to(cx - radius, cy)
         << line(radius * 2, 0);
}

void CNextPlayerWidget::Handle(const event&)
{
}