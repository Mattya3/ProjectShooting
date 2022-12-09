#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <bits/stdc++.h>
#include <component/Image.hpp>
#include <filesystem>
#include <png.h>
#include <stdexcept>

using namespace std;
using std::filesystem::current_path;
int PngTexture::tid = 0;

PngTexture::PngTexture(const string &fname, Location loc) : loc(loc) {
    filename = (current_path() / filesystem::path("img/" + fname)).c_str();
    id = tid; // 各テクスチャに固有可する
    ++tid;
    cout << filename << " as " << tid << endl;
    init();
}
PngTexture::PngTexture() {}
PngTexture::~PngTexture() { final(); }
void PngTexture::view() {
    glColor3d(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, id);
    glEnable(GL_TEXTURE_2D);
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(loc.sx, loc.sy, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(loc.sx + loc.xlen, loc.sy, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(loc.sx + loc.xlen, loc.sy + loc.ylen, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(loc.sx, loc.sy + loc.ylen, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
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
void PngTexture::view_clone(Location loca) {
    glColor3d(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, id);
    glEnable(GL_TEXTURE_2D);
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(loca.sx, loca.sy, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(loca.sx + loca.xlen, loca.sy, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(loca.sx + loca.xlen, loca.sy + loca.ylen, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(loca.sx, loca.sy + loca.ylen, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void PngTexture::final() { free(data); }

unsigned char *PngTexture::rawData() { return data; }

unsigned int PngTexture::getID() { return id; }

unsigned int PngTexture::getWidth() { return width; }

unsigned int PngTexture::getHeight() { return height; }