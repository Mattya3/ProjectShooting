#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <bits/stdc++.h>
#include <component/Image.hpp>
#include <png.h>
#include <stdexcept>
using namespace std;


PngTexture::PngTexture(const std::string &fname, unsigned int tid) {
    filename = fname;
    id = tid;
    cout << filename << endl;
    init();
}

PngTexture::~PngTexture() { final(); }

void PngTexture::init() {
    // png画像ファイルのロード
    png_structp sp =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop ip = png_create_info_struct(sp);
    FILE *fp = fopen(filename.c_str(), "rb");
    if(!fp) {
        perror(filename.c_str());
    }
    png_init_io(sp, fp);
    png_read_info(sp, ip);
    png_get_IHDR(sp, ip, (png_uint_32 *)&width, (png_uint_32 *)&height, &depth,
                 &colortype, &interlacetype, NULL, NULL);
    // メモリ領域確保
    int rb = png_get_rowbytes(sp, ip);
    data = new ubyte_t[height * rb];
    ubyte_t **recv = new ubyte_t *[height];
    for(int i = 0; i < height; i++)
        recv[i] = &data[i * rb];
    png_read_image(sp, recv);
    png_read_end(sp, ip);
    png_destroy_read_struct(&sp, &ip, NULL);
    fclose(fp);
    delete[] recv;

    // テクスチャへの登録
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA,
                      GL_UNSIGNED_BYTE, data);
}

void PngTexture::final() { free(data); }

unsigned char *PngTexture::rawData() { return data; }

unsigned int PngTexture::getID() { return id; }

unsigned int PngTexture::getWidth() { return width; }

unsigned int PngTexture::getHeight() { return height; }