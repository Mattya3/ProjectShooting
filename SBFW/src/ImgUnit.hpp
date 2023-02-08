#pragma once
#include "math2D/DataOf2D.hpp"

namespace sbfw {

// Atlas UNItも作る texposも入れて
// Shape Unit も作る opengの単純な図形を描画できる
namespace texture {
static int current_bind_id = 0;

/// @brief 画像と配置箇所を管理する描画の単位
class ImgUnit {
  public:
    /// @brief 不動の画像を描画するクラスのコンストラクタ
    /// @param pos 描画位置
    /// @param id bind id
    /// @param len 画像の大きさ
    /// @param scale 画像の表示時の倍率 (任意)
    ImgUnit(DataOf2D pos, int id, DataOf2D len, float scale)
        : pos(pos), len(len), this_id(id), scale(scale) {}
    ImgUnit(DataOf2D pos, int id, DataOf2D len) : ImgUnit(pos, id, len, 1.0) {}
    ImgUnit() = default;

    /// @brief 事前に設定された位置にPNG画像を描画する
    void Draw();

    /// @brief 描画する画像を差し替える
    /// @param new_id 差し替えたい画像のbind id
    /// @param len_ 差し替え先画像の大きさ
    void change(int new_id, DataOf2D len_) {
        this_id = new_id;
        len = len_;
    }

  public:
    DataOf2D len;
    float scale;
    DataOf2D pos;
    int this_id;
};

} // namespace texture
} // namespace sbfw
