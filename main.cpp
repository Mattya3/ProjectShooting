// #include "../include/funcA.hpp"
#define GL_SILENCE_DEPRECATION 1
#include <funcA.hpp>

#include <bits/stdc++.h>
using namespace std;
// #ifdef COMPILE__AT__MAC__OS
#include <OpenGL/OpenGL.h>
#include <glu.h>
#include <gl.h>
#include <OpenGL.h>
#include <GLFW/glfw3.h>
// #endif

const GLfloat lightPosition1[4] = {0.0f,3.0f, 5.0f, 1.0f};
const GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat lightPosition2[4] = {5.0f,3.0f, 0.0f, 1.0f};
const GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };

const GLfloat teapotAmbient[4] = {0.3f,0.5f, 0.0f, 1.0f};
const GLfloat teapotDiffuse[4] = {1.0f,1.0f, 0.3f, 1.0f};
const GLfloat teapotSpecular[4] = {1.0f,1.0f, 1.0f, 1.0f};
const GLfloat teapotShininess[4] = {20.0f};

void setup(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT0, GL_SPECULAR, red);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapotAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapotDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glutSolidTeapot(0.5);
    glFlush();
}


void resize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,
                   (double)width/height,
                   0.1,
                   100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-0.5, 2.1, 2.0,
              0.0, 0.0, 0.0,
              0.0, 4.0, 0.0);
}
void display(void){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glutWireTeapot(0.5);
    glFlush();
}


// int main(int argc, char * argv[]) {
//     // // insert code here...
//     // glutInit(&argc, argv);
//     // glutInitWindowSize(600,600);
//     // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
//     // glutCreateWindow("Wire_teapot");
//     // glutReshapeFunc(resize);
//     // glutDisplayFunc(draw);
//     setup();
//     glutMainLoop();
//     cout << 1 << "\n";
//     return 0;
// }
static void glfwError(int id, const char* description)
{
  std::cout << description << std::endl;
}

int main(){
  glfwSetErrorCallback(&glfwError);
  glfwInit();
  // GLFWを初期化する
  if (glfwInit() == GL_FALSE) {
	// 初期化に失敗
    cerr << "Can't initialize GLFW" << endl;
    glfwTerminate();
    return 1;
  }
  // Setup GLFW window properties
  // OpenGLのバージョン指定 4.1
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // 古い機能を削除したプロファイルを使用するか
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // OpenGLのプロファイルを指定する
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* mainWindow = glfwCreateWindow(640,480,"Sample Window", NULL, NULL);
  if(mainWindow == NULL){
    // ウィンドウの作成に失敗
    cerr << "Can't create GLFW window" << endl;
    glfwTerminate();
    return 1;
  }
  // ウィンドウをOpenGLの処理対象にする
  glfwMakeContextCurrent(mainWindow);
  // 背景色を指定
  // 引数は 0～1のfloat型で r g b a を指定する。今回は不透明の赤100%
  glClearColor(1.0f,0.0f,0.0f,1.0f);
  // ウィンドウが閉じるまでループする
  while(glfwWindowShouldClose(mainWindow) == GL_FALSE){
    // ウィンドウを消去する
    glClear(GL_COLOR_BUFFER_BIT);
    // 
    //  ここで描画処理
    //
    // カラーバッファを入れ替える
    glfwSwapBuffers(mainWindow);
    
    // イベントを取り出す (ユーザーのインプットイベントなどなどを取り扱います。)
    glfwPollEvents();
  } 
}