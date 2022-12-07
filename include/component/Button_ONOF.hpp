#pragma once
#include <component/ButtonBase.hpp>
using namespace std;

class Button_ONOF : public ButtonBase {
  using ButtonBase::ButtonBase;

  public:
    virtual void action_when_pushed() override;
};
