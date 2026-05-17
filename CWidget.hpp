#pragma once
#include "graphics.hpp"

class CWidget
{
protected:
    int x;
    int y;
    int w;
    int h;

public:
    CWidget(int x_, int y_, int w_, int h_);
    virtual ~CWidget() = default;

    bool Contains(int px, int py) const;

    virtual void Draw() const = 0;
    virtual void Handle(const genv::event& ev) = 0;
};
