#include "CSpinbox.hpp"
#include <string>

using namespace genv;

CSpinbox::CSpinbox(int x_, int y_, int w_, int h_, int min_, int max_, int kezdo_)
    : CWidget(x_, y_, w_, h_), aktiv(false)
{
    minimum = min_;
    maximum = max_;
    ertek = kezdo_;

    if (ertek < minimum) ertek = minimum;
    if (ertek > maximum) ertek = maximum;
}

int CSpinbox::Ertek() const
{
    return ertek;
}

void CSpinbox::Draw() const
{
    gout << color(230, 230, 230)
         << move_to(x, y)
         << box(w, h);

    int gombw = 30;
    int valaszto_x = x + w - gombw;

    gout << color(180, 180, 180)
         << move_to(valaszto_x, y)
         << box(gombw, h / 2);

    gout << move_to(valaszto_x, y + h / 2)
         << box(gombw, h - h / 2);

    std::string sz = std::to_string(ertek);
    int szx = x + 10;
    int szy = y + h / 2 - 10;

    gout << move_to(szx, szy)
         << color(0, 0, 0)
         << text(sz);

    gout << move_to(valaszto_x + 10, y + h / 4 - 10)
         << text("+");

    gout << move_to(valaszto_x + 12, y + 3 * h / 4 - 10)
         << text("-");
}

void CSpinbox::Handle(const event& ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left)
    {
        aktiv = Contains(ev.pos_x, ev.pos_y);

        int gombw = 30;
        int valaszto_x = x + w - gombw;

        if (ev.pos_x >= valaszto_x && ev.pos_x < x + w &&
            ev.pos_y >= y && ev.pos_y < y + h / 2)
        {
            ertek++;
        }
        else if (ev.pos_x >= valaszto_x && ev.pos_x < x + w &&
                 ev.pos_y >= y + h / 2 && ev.pos_y < y + h)
        {
            ertek--;
        }
    }

    if (aktiv && ev.type == ev_key)
    {
        if (ev.keycode == key_up)   ertek++;
        if (ev.keycode == key_down) ertek--;

        if (ev.keycode == key_pgup) ertek += 10;
        if (ev.keycode == key_pgdn) ertek -= 10;
    }

    if (ertek < minimum) ertek = minimum;
    if (ertek > maximum) ertek = maximum;
}