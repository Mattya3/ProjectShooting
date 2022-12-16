#pragma once
#include <component/ButtonBase.hpp>

class NextSceneButton : public ButtonBase {
    using ButtonBase::ButtonBase;

  public:
    bool next_scene = false;
    void action_when_pushed() override {
        btn_enable = true;
        next_scene = true;
    }
    ~NextSceneButton(){}
 };