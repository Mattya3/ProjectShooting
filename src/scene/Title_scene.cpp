#include <scenes/Title_Scene.hpp>

#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/ChangeStructureView.hpp>
#include <scenes/ResolverCallbackFunc.hpp>

double sx, sy, xlen, ylen;
static void render2() {
    glColor3d(1.0, 1.0, 1.0);
    static const GLfloat diffuse[] = {0.6, 0.1, 0.1, 1.0};
    static const GLfloat specular[] = {0.3, 0.3, 0.3, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);

    glBindTexture(GL_TEXTURE_2D, 1);
    glEnable(GL_TEXTURE_2D);
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTranslated(sx, sy, 0);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-0.5, -0.5, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(0.5, -0.5, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(0.5, 0.5, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-0.5, 0.5, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 2);
    glEnable(GL_TEXTURE_2D);
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(sx, sy, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(sx + xlen, sy, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(sx + xlen, sy + ylen, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(sx, sy + ylen, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
Title_scene::Title_scene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);

    sy = sx = -1.0;
    xlen = ylen = 0.3;
    PngTexture pt("ic_launcher.png", 1);
    PngTexture me_img("battle/me.png", 2);

    NextSceneButton *b = new NextSceneButton(-0.2, -0.2, 0.4, 0.4);
    Button_anyTimes *transBtn = new Button_anyTimes(0.3, 0.3, 0.5, 0.5);
    b->set_color(0.5, 0.1, 0.8);
    this->add_button(b);
    transBtn->set_color(0.1, 0.8, 0.2);
    this->add_button(transBtn);

    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        render2();
        show_component();
        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(transBtn->is_pushed()) {
            sx += 0.05;
            sy += 0.05;
            if(sx >= 1 && sy >= 1) {
                sx = sy = -1;
            }
        }
        if(b->next_scene) {
            break;
        }
    }
    if(b->next_scene) {
        ChangeStructureView csv(window1);
    }
}
void Title_scene::render(GLFWwindow *window1) {
    
}
Title_scene::~Title_scene() {}