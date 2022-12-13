#include <scenes/Scene.hpp>
class BattleScene : Scene {
  private:
  // キーcallback用変数
    bool wp = false, ap = false, sp = false, dp = false;

    double velocity = 0.08;
    vector<Location> bullets_loc, // 自機の弾の位置
        bullets_loc_enemy;        // 敵の弾の位置

    // 画面上の要素
    // ポインタでないとオーバーライドができないのでスマートポインタで宣言
    unique_ptr<PngTexture> my_fighter, // 自機
        bullet,                        // 弾 clone_viewにより一つ宣言すれば十分
        bullet_enemy;                  // 敵の弾
    vector<unique_ptr<PngTexture>> enemies; // 敵たち
    unique_ptr<NextSceneButton> btn_go_next_scene;
    private:
    /**
     * @brief 
     * 画面上にもう描画されない弾を削除する
     * 正確にはbullets_locから消す。
    */
   void remove_faraway_bullets();
  public:
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override;

    BattleScene(GLFWwindow *window1);
    ~BattleScene();
};
