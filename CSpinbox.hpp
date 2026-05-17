#pragma once
#include "CWidget.hpp"

class CSpinbox : public CWidget
{
protected:
    int ertek;
    int minimum;
    int maximum;
    bool aktiv;

public:
    CSpinbox(int x_, int y_, int w_, int h_, int min_, int max_, int kezdo_);

    void Draw() const override;
    void Handle(const genv::event& ev) override;

    int Ertek() const;
};