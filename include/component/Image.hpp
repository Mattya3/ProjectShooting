#pragma once
#include <component/Location.hpp>
#include <string>
typedef unsigned char ubyte_t;
// imgディレクトリであることは前提とする
class PngTexture {
    static int tid;
    unsigned int id; // テクスチャID
    ubyte_t *data;   // 生データを保持する
    unsigned int width, height;
    int depth, colortype, interlacetype;
    std::string filename;

    void init();
    void final();
    ubyte_t *rawData();

  public:
    Location loc;
    PngTexture();
    PngTexture(const std::string &fname, Location loc);
    ~PngTexture();
    void view();
    void view_clone(Location loc);

    unsigned int getID();

    unsigned int getWidth();
    unsigned int getHeight();
};
