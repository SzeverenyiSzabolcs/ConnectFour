#include "CButton.hpp"

using namespace genv;

CButton::CButton(int x_, int y_, int w_, int h_, const std::string& label_, std::function<void()> on_click_)
    : CWidget(x_, y_, w_, h_), label(label_), on_click(on_click_)
{
}

void CButton::Draw() const
{
    gout << color(230, 230, 230)
         << move_to(x, y)
         << box(w, h);

    gout << color(30, 30, 30)
         << move_to(x, y)
         << line(w, 0)
         << line(0, h)
         << line(-w, 0)
         << line(0, -h);

    int tx = x + (w - gout.twidth(label)) / 2;
    int ty = y + h / 2 + (gout.cascent() - gout.cdescent()) / 2 -20;

    gout << move_to(tx, ty)
         << text(label);
}

void CButton::Handle(const event& ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left && Contains(ev.pos_x, ev.pos_y))
    {
        if (on_click)
        {
            on_click();
        }
    }
}
