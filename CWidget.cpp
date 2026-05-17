#include "CWidget.hpp"

CWidget::CWidget(int x_, int y_, int w_, int h_)
    : x(x_), y(y_), w(w_), h(h_)
{
}

bool CWidget::Contains(int px, int py) const
{
    return px >= x && px < x + w && py >= y && py < y + h;
}
