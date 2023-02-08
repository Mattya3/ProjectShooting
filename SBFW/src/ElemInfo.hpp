#pragma once
#include "math2D/DataOf2D.hpp"

#include <bits/stdc++.h>

namespace sbfw {
/**
 * @brief ユーザが定義してSBFWに渡す情報
 * ファイル名と、表示位置
 */
struct ElemInfo {
  public:
    ElemInfo() = default;
    ElemInfo(DataOf2D pos, std::string fname)
        : pos(pos), img_fname(fname), scale(1.0f) {}
    ElemInfo(DataOf2D pos, std::string fname, float scale)
        : pos(pos), img_fname(fname), scale(scale) {}

    DataOf2D pos;
    std::string img_fname;
    float scale;
};
/**
 * @brief 後で画面上の要素にアクセスするための構造体
 * ElemInfoを渡し、SBFW側から戻されるもの
 * あとからButtonやimageの画像を変更したい時、ElemKeyをchange_imageにわたす。
 */
class ElemKey {
  public:
    /**
     * @brief 要素の種類を表すEnum
     */
    enum class ele_type { btn, img };

    explicit ElemKey() = default;
    explicit ElemKey(ele_type e_, int k) : e(e_), key_id(k) {}
    ele_type e;
    int key_id;
};
} // namespace sbfw
