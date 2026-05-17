#include "CStatusWidget.hpp"
#include "CGameMaster.hpp"
#include "graphics.hpp"

using namespace genv;

CStatusWidget::CStatusWidget(int x_, int y_, int w_, int h_, CGameMaster* game_)
    : CWidget(x_, y_, w_, h_), game(game_)
{
}

void CStatusWidget::Draw() const
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

    std::string status = game->StatusText();
    std::string line2 = "Esc: Kilépés";

    gout << move_to(x + 12, y + 28 -20)
         << text(status)
         << move_to(x + 12, y + 56-20)
         << text(line2);
}

void CStatusWidget::Handle(const event&)
{
}
