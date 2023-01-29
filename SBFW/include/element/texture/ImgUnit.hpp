#pragma once
#include <DataOf2D.hpp>
#include <GLFW/glfw3.h>
namespace sbfw {

// Atlas UNItも作る texposも入れて
// Shape Unit も作る opengの単純な図形を描画できる
namespace texture {
static int current_bind_id = 0;

class ImgUnit {
  public:
    DataOf2D len;
    float scale;
    DataOf2D pos;
    int this_id;

  public:
    ImgUnit(DataOf2D pos, int id, DataOf2D len)
        : pos(pos), len(len), this_id(id), scale(1.0f) {}
    ImgUnit(DataOf2D pos, int id, DataOf2D len, float scale)
        : pos(pos), len(len), this_id(id), scale(scale) {}
    ImgUnit() = default;

    void view() {
        // glColor3d(1.0, 1.0, 1.0);
        // if(current_bind_id != this_id) {
            glBindTexture(GL_TEXTURE_2D, this_id);
            // current_bind_id = this_id;
        // }
        glColor3d(1.0, 1.0, 1.0);

        glEnable(GL_TEXTURE_2D);
        glNormal3d(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);
        glVertex3d(pos.x - len.x / 2 * scale, pos.y - len.y / 2 * scale, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex3d(pos.x + len.x / 2 * scale, pos.y - len.y / 2 * scale, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex3d(pos.x + len.x / 2 * scale, pos.y + len.y / 2 * scale, 0.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(pos.x - len.x / 2 * scale, pos.y + len.y / 2 * scale, 0.0);

        glTranslatef(pos.x - len.x / 2, pos.y - len.y, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    void change(int new_id, DataOf2D len_) {
        this_id=new_id;
        len = len_;
    }
};

} // namespace texture
} // namespace sbfw
