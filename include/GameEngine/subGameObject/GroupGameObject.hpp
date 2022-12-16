#include <GameEngine/subGameObject/GameObjectBase.hpp>
#include <bits/stdc++.h>
#include <component/Image.hpp>
#include <zip.hpp>
using namespace std;
/**
 * 画像は同一だが複数出現する物
 */
class GroupGameObject {
  private:
    PngTexture common_tex = PngTexture("battle/bulletMe.png");
    vector<DataOf2D> _vg;   // 中心座標を保持するクラス
    vector<DataOf2D> _vels; // 速度ベクトルを保持するクラス
    DataOf2D len;
    DataOf2D initial_vel = DataOf2D(0.008, 0.006);

  public:
    GroupGameObject(/* args */) {
        len = DataOf2D(common_tex.getWidth(), common_tex.getHeight(), 1.0);
    }
    void push(DataOf2D cxy) {
        _vg.emplace_back(cxy);
        _vels.emplace_back(initial_vel);
    }
    void view() {
        for(auto &&e : _vg) {
            Location t = CenterLocation(e, len).to_Location();
            common_tex.view_clone(t);
        }
    }
    void proceed() {
        for(size_t i = 0; i < _vg.size(); i++) {
            _vg[i] += _vels[i];
        }
    }
    void reflect(CenterLocation domain) {
        auto fixed_domain =
            CenterLocation(domain.get_cxy(), domain.get_len() - len);
        for(size_t i = 0; i < _vg.size(); i++) {
            if(_vg[i].x < fixed_domain.left() ||
               fixed_domain.right() < _vg[i].x) {
                _vels[i].x *= -1;
            }
            if(_vg[i].y < fixed_domain.down() || fixed_domain.up() < _vg[i].y) {
                _vels[i].y *= -1;
            }
        }
    }
    ~GroupGameObject() {}
};
