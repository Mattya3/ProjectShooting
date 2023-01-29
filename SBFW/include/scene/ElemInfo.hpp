#pragma once
#include <DataOf2D.hpp>

namespace sbfw {
// ユーザが定義してSBFWに渡す情報
// ファイル名と、表示位置
class ElemInfo {
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

// ElemInfoを渡し、SBFW側から戻されるもの
// あとからButtonやimageの画像を変更したい時、ElemKeyをchange_imageにわたす。
class ElemKey {
  public:
    enum class ele_type { btn, img };
    ElemKey() = default;
    ElemKey(ele_type e_, int k) : e(e_), key_id(k) {}
    ele_type e;
    int key_id;
};
} // namespace sbfw
