#pragma once
#include <DataOf2D.hpp>
#include <GLFW/glfw3.h>
#include "Location.hpp"
#include <string>
typedef unsigned char ubyte_t;
//  SBFWで等価な機能が存在するが、internal側の複雑な座標系に対応するための関数群が
// このクラスに準じて作られているため存続させる
// imgディレクトリであることは前提とする
class PngTexture {
    static int tid;
    unsigned int id; // テクスチャID
    unsigned int width, height;
    int depth, colortype, interlacetype;
    std::string filename;

    void init();
    // void final();
    // ubyte_t *rawData();

  public:
    Location loc;
    PngTexture();
    PngTexture(const std::string &fname);
    PngTexture(const std::string &fname, Location loc);
    ~PngTexture();
    void view();
    void view_clone(Location loc);
    void view_clone(Location loca, vector<double> col_vec);
    void view(DataOf2D pos, float ratio = 1.0,
              const vector<float> &col = vector<float>(3, 1.0));
    unsigned int getID();

    unsigned int getWidth();
    unsigned int getHeight();
};
