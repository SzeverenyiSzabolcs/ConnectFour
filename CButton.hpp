#pragma once
#include "CWidget.hpp"
#include <functional>
#include <string>

class CButton : public CWidget
{
private:
    std::string label;
    std::function<void()> on_click;

public:
    CButton(int x_, int y_, int w_, int h_, const std::string& label_, std::function<void()> on_click_);

    void Draw() const override;
    void Handle(const genv::event& ev) override;
};
