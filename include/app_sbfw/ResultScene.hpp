#include <extension/NumberDisplay.hpp>
#include <sbfw.hpp>

#include <bits/stdc++.h>

class ResultScene :public sbfw::scene::SimpleScene {
  private:
    sbfw::ext::NumberDisplay score_display;
    void layer_front() override;

  public:
    ResultScene() {}
};
