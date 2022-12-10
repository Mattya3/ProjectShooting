#include <scenes/Scene.hpp>
class BattleScene : Scene {
  private:
    double velocity = 0.08;
    bool wp = false, ap = false, sp = false, dp = false;
    unique_ptr<PngTexture> my_fighter, bullet;
    vector<Location> bullets_loc;

  public:
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override;

    BattleScene(GLFWwindow *window1);
    ~BattleScene();
};
