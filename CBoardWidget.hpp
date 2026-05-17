#pragma once
#include "CWidget.hpp"

class CGameMaster;

class CBoardWidget : public CWidget
{
private:
    CGameMaster* game;
    int top_area;
    int cell_size;

public:
    CBoardWidget(int x_, int y_, CGameMaster* game_);

    void Draw() const override;
    void Handle(const genv::event& ev) override;

private:
    int ColumnFromPixel(int px) const;
};
