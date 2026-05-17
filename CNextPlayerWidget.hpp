#pragma once
#include "CWidget.hpp"

class CGameMaster;

class CNextPlayerWidget : public CWidget
{
private:
    CGameMaster* game;

public:
    CNextPlayerWidget(int x_, int y_, int w_, int h_, CGameMaster* game_);

    void Draw() const override;
    void Handle(const genv::event& ev) override;
};