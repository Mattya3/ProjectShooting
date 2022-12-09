#pragma once
#include <string>
#include <component/Location.hpp>
typedef unsigned char ubyte_t;
// imgディレクトリであることは前提とする
class PngTexture {
    unsigned int id; // テクスチャID
    ubyte_t *data;   // 生データを保持する
    unsigned int width, height;
    int depth, colortype, interlacetype;
    std::string filename;
    Location loc;

    void init();
    void final();
    ubyte_t *rawData();

  public:
    PngTexture();
    PngTexture(const std::string &fname, unsigned int tid, Location loc);
    ~PngTexture();
    void view();
    
    unsigned int getID();

    unsigned int getWidth();
    unsigned int getHeight();
};
