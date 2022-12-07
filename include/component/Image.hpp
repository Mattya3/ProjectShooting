#pragma once
#include <string>

typedef unsigned char ubyte_t;
// imgディレクトリであることは前提とする
class PngTexture {
    unsigned int id; // テクスチャID
    ubyte_t *data;   // 生データを保持する
    unsigned int width, height;
    int depth, colortype, interlacetype;
    std::string filename;

    void init();
    void final();

  public:
    PngTexture();
    PngTexture(const std::string &, unsigned int);
    ~PngTexture();
    ubyte_t *rawData();
    unsigned int getID();

    unsigned int getWidth();
    unsigned int getHeight();
};
