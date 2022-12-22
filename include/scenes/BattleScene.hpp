#include <GameEngine/Game.hpp>
#include <component/Image.hpp>
#include <component/RemainingStatus.hpp>
#include <internal/battle/Battle.hpp>

#include <scenes/Scene.hpp>
class BattleScene : Scene {
    using Scene::Scene;

  private:
    // キーcallback用変数
    bool wp = false, ap = false, sp = false, dp = false, spacep = false;
    Game game;
    PngTexture heart = PngTexture("status/redheart.png");
    PngTexture gray_heart = PngTexture("status/redheart.png");
    RemainingStatus life = RemainingStatus(DataOf2D(0.3, 0), heart, gray_heart, 5);
    vector<Location> bullets_loc_enemy; // 敵の弾の位置

    // 画面上の要素
    // ポインタでないとオーバーライドができないのでスマートポインタで宣言
    vector<unique_ptr<PngTexture>> enemies; // 敵たち
    NextSceneButton *btn_go_next_scene;

  private:
  public:
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override;

    BattleScene(GLFWwindow *window1);
    ~BattleScene();
};
