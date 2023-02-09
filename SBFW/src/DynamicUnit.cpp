#include "DynamicUnit.hpp"

#include <GLFW/glfw3.h>
namespace sbfw {
namespace texture {

DynamicUnit::DynamicUnit() {}
void DynamicUnit::Draw(DataOf2D pos) { Draw(pos, 1.0f); }

void DynamicUnit::Draw(DataOf2D pos, float scale) {
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

} // namespace texture
} // namespace sbfw