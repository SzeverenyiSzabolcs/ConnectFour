#include "CListbox.hpp"

using namespace genv;

CListbox::CListbox(int x_, int y_, int w_, int h_, const std::vector<std::string>& elemek_)
    : CWidget(x_, y_, w_, h_), aktiv(false)
{
    elemek = elemek_;
    kivalasztott = elemek.empty() ? -1 : 0;
    elso_lathato = 0;
    sor_magassag = 25;
    lathato_db = h / sor_magassag;

    if (lathato_db < 1) lathato_db = 1;
}

std::string CListbox::Ertek() const
{
    if (kivalasztott >= 0 && kivalasztott < (int)elemek.size())
        return elemek[kivalasztott];

    return "";
}

int CListbox::Index() const
{
    return kivalasztott;
}

void CListbox::Draw() const
{
    gout << color(240, 240, 240)
         << move_to(x, y)
         << box(w, h);

    for (int i = 0; i < lathato_db; i++)
    {
        int index = elso_lathato + i;
        if (index >= (int)elemek.size()) break;

        int sor_y = y + i * sor_magassag;

        if (index == kivalasztott)
        {
            gout << color(180, 200, 255)
                 << move_to(x + 1, sor_y + 1)
                 << box(w - 2, sor_magassag - 2);
        }

        gout << color(200, 200, 200)
             << move_to(x, sor_y)
             << line(w, 0);

        gout << color(0, 0, 0)
             << move_to(x + 5, sor_y + sor_magassag / 2 - 10)
             << text(elemek[index]);
    }
}

void CListbox::Handle(const event& ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left)
    {
        aktiv = Contains(ev.pos_x, ev.pos_y);

        if (aktiv)
        {
            int melyik_sor = (ev.pos_y - y) / sor_magassag;
            int index = elso_lathato + melyik_sor;

            if (index >= 0 && index < (int)elemek.size())
            {
                kivalasztott = index;
            }
        }
    }

    if (aktiv && ev.type == ev_key)
    {
        if (ev.keycode == key_down)
        {
            if (kivalasztott < (int)elemek.size() - 1)
                kivalasztott++;
        }

        if (ev.keycode == key_up)
        {
            if (kivalasztott > 0)
                kivalasztott--;
        }

        if (ev.keycode == key_pgdn)
        {
            kivalasztott += lathato_db;
            if (kivalasztott >= (int)elemek.size())
                kivalasztott = (int)elemek.size() - 1;
        }

        if (ev.keycode == key_pgup)
        {
            kivalasztott -= lathato_db;
            if (kivalasztott < 0)
                kivalasztott = 0;
        }

        if (kivalasztott < elso_lathato)
            elso_lathato = kivalasztott;

        if (kivalasztott >= elso_lathato + lathato_db)
            elso_lathato = kivalasztott - lathato_db + 1;
    }
}