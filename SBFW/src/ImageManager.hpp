#pragma once
#include "math2D/DataOf2D.hpp"

#include <bits/stdc++.h>
namespace sbfw {

namespace texture {

/// @brief PNGデータとGLFWの対応を管理するクラス
class ImageManager {
  private:
    using string = std::string;

  public:
    ImageManager() = default;
    /// @brief png画像を無駄なく読み込む。同じものはキャッシュで対応
    /// @param fname ファイル名
    /// @return bind_idと画像の縦横幅
    std::pair<int, DataOf2D> ProvideImage(string const &fname);

    std::tuple<int, DataOf2D, int, int> ProvideImageGetWH(string const &fname);

  private:
    /// @brief ファイル名が読み込み済みか検証する
    /// @param fname ファイル名
    /// @return すでに読み込んだことがあるならbind_id、そうでないなら-1
    int IsAlreadyLoaded(string const &fname);

    /// @brief lordpngライブラリを用いてPNG画像をOpenGLにbindid=引数で読み込む
    /// @param fullpath_fname ファイル名
    /// @param id OpenGLに紐付ける用のbind_id
    /// @return 画像の横幅縦幅
    std::pair<int, int> LoadPng(std::string const &fullpath_fname, int id);

    /// @brief 画像のサイズ(w,h)を正規化座標系へ変換する
    /// @param w 横幅
    /// @param h 縦幅
    /// @return 正規化座標系での(横幅, 縦幅) [0,1]
    inline DataOf2D GetRegularLen(uint32_t w, uint32_t h);

  private:
    // OpenGLのbind id
    int id = -1;
    // 無駄をなくすため同じファイル名をすでに読み込んでいないか調べられるようにする。
    std::unordered_map<string, int> loaded_pngs;
    std::vector<DataOf2D> len_data;
    std::vector<std::pair<int, int>> len_data_un_reg;
};

} // namespace texture

} // namespace sbfw
