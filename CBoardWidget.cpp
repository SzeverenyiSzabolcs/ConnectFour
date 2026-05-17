#include "CBoardWidget.hpp"
#include "CGameMaster.hpp"
#include "graphics.hpp"
#include <algorithm>
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

CBoardWidget::CBoardWidget(int x_, int y_, CGameMaster* game_)
    : CWidget(x_, y_, 560, 520), game(game_), top_area(40), cell_size(80)
{
}

void CBoardWidget::Draw() const
{
    // top selector area
    gout << color(230, 230, 230)
         << move_to(x, y)
         << box(w, top_area);

    int selected = game->GetSelectedColumn();
    gout << color(200, 200, 200)
         << move_to(x + selected * cell_size, y)
         << box(cell_size, top_area);

    std::string marker = "v";
    int mx = x + selected * cell_size + (cell_size - gout.twidth(marker)) / 2;
    int my = y + top_area / 2 + (gout.cascent() - gout.cdescent()) / 2 - 20;
    gout << color(30, 30, 30)
         << move_to(mx, my)
         << text(marker);

    // board background
    gout << color(25, 80, 200)
         << move_to(x, y + top_area)
         << box(w, h - top_area);

    for (int row = 0; row < CGameMaster::ROWS; ++row)
    {
        for (int col = 0; col < CGameMaster::COLS; ++col)
        {
            int cell_x = x + col * cell_size;
            int cell_y = y + top_area + row * cell_size;
            int center_x = cell_x + cell_size / 2;
            int center_y = cell_y + cell_size / 2;
            int value = game->GetCell(row, col);

            if (value == 1)
            {
                draw_filled_circle(center_x, center_y, 30, 220, 40, 40);
            }
            else if (value == 2)
            {
                draw_filled_circle(center_x, center_y, 30, 240, 220, 40);
            }
            else
            {
                draw_filled_circle(center_x, center_y, 30, 245, 245, 245);
            }

            gout << color(15, 45, 130)
                 << move_to(cell_x, cell_y)
                 << line(cell_size, 0)
                 << line(0, cell_size)
                 << line(-cell_size, 0)
                 << line(0, -cell_size);
        }
    }

    gout << color(30, 30, 30)
         << move_to(x, y)
         << line(w, 0)
         << line(0, h)
         << line(-w, 0)
         << line(0, -h);
}

void CBoardWidget::Handle(const event& ev)
{
    if (ev.type == ev_mouse && Contains(ev.pos_x, ev.pos_y))
    {
        int column = ColumnFromPixel(ev.pos_x);
        if (column != -1)
        {
            game->SetSelectedColumn(column);
            if (ev.button == btn_left)
            {
                game->DropInColumn(column);
            }
        }
    }
}

int CBoardWidget::ColumnFromPixel(int px) const
{
    if (px < x || px >= x + w)
    {
        return -1;
    }

    int column = (px - x) / cell_size;
    if (column < 0 || column >= CGameMaster::COLS)
    {
        return -1;
    }
    return column;
}
