#pragma once
#include <DataOf2D.hpp>
#include <component/Location.hpp>
#include <GLFW/glfw3.h>
#include <string>
typedef unsigned char ubyte_t;
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
    void view(DataOf2D pos, float ratio = 1.0,
              const vector<float> &col = vector<float>(3, 1.0)) {
        float w = width / Setting::WINDOW_width,
              h = height / Setting::WINDOW_height;
        glEnable(GL_TEXTURE_2D);
        glNormal3d(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glColor3d(col[0], col[1], col[2]);
        glTexCoord2d(0, 0 + 1);
        glVertex3d(pos.x - w * ratio, pos.y - h * ratio, 0.0);
        glTexCoord2d(0 + 1, 0 + 1);
        glVertex3d(pos.x + w * ratio, pos.y - h * ratio, 0.0);
        glTexCoord2d(0 + 1, 0);
        glVertex3d(pos.x + w * ratio, pos.y + h * ratio, 0.0);
        glTexCoord2d(0, 0);
        glVertex3d(pos.x - w * ratio, pos.y + h * ratio, 0.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    unsigned int getID();

    unsigned int getWidth();
    unsigned int getHeight();
};
