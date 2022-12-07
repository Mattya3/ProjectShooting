#pragma once
#include <component/ButtonBase.hpp>
class Button_anyTimes : public ButtonBase {
    using ButtonBase::ButtonBase;

  private:
    bool _is_pushed = false;

  public:
    inline bool is_pushed() override {
        bool t = _is_pushed;
        _is_pushed = false;
        return t;
    }
    void action_when_pushed() override { _is_pushed = true; }
};
