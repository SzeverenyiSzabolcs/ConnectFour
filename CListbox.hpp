#pragma once
#include "CWidget.hpp"
#include <vector>
#include <string>

class CListbox : public CWidget
{
protected:
    std::vector<std::string> elemek;
    int kivalasztott;
    int elso_lathato;
    int sor_magassag;
    int lathato_db;
    bool aktiv;

public:
    CListbox(int x_, int y_, int w_, int h_, const std::vector<std::string>& elemek_);

    void Draw() const override;
    void Handle(const genv::event& ev) override;

    std::string Ertek() const;
    int Index() const;
};