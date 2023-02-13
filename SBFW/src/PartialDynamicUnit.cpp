#include "PartialDynamicUnit.hpp"

#include <GLFW/glfw3.h>

namespace sbfw::texture {

PartialDynamicUnit::PartialDynamicUnit(
    int sx, int sy, int w, int h, std::tuple<int, DataOf2D, int, int> info) {
    auto [bind_id, img_reg_len_data, whole_w, whole_h] = info;
    this_id = bind_id;

    tleft = float(sx) / float(whole_w);
    float tw = float(w) / float(whole_w);
    tdown = float(sy) / float(whole_h);
    float th = float(h) / float(whole_h);
    tright = tleft + tw;
    tup = tdown + th;

    partial_img_len = GetRegularLen(w, h);
    len=partial_img_len;
    // len = img_reg_len_data;
}

void PartialDynamicUnit::Draw(DataOf2D pos) { Draw(pos, 1.0f); }

void PartialDynamicUnit::Draw(DataOf2D pos, float ratio) {
    glBindTexture(GL_TEXTURE_2D, this_id);
    glColor3d(1.0, 1.0, 1.0);

    glEnable(GL_TEXTURE_2D);
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    // glColor3d(col[0], col[1], col[2]);
    glTexCoord2d(tleft, tup);
    glVertex3d(pos.x - partial_img_len.x * ratio,
               pos.y - partial_img_len.y * ratio, 0.0);
    glTexCoord2d(tright, tup);
    glVertex3d(pos.x + partial_img_len.x * ratio,
               pos.y - partial_img_len.y * ratio, 0.0);
    glTexCoord2d(tright, tdown);
    glVertex3d(pos.x + partial_img_len.x * ratio,
               pos.y + partial_img_len.y * ratio, 0.0);
    glTexCoord2d(tleft, tdown);
    glVertex3d(pos.x - partial_img_len.x * ratio,
               pos.y + partial_img_len.y * ratio, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

} // namespace sbfw::texture
