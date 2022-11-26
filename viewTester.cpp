#define GL_SILENCE_DEPRECATION 1
// #include <funcA.hpp>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;
constexpr int WINDOW_width = 800, WINDOW_height = 700;
int main() {

    GLFWwindow *window1, *window2;

    // ライブラリglfw の初期化
    if(!glfwInit())
        return -1;

    // ウィンドウを作成
    window1 = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window1) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window1);
    
    // 描画テスト関数 start (x,y)からそのどこまで伸ばすかを指定する。
    // 左下が原点(0,0)とする
    // 座標系は x=[0,800] , y=[0,700] 
    auto show = [](double sx, double sy, double xlen, double ylen,
                   string color) {
        sx /= WINDOW_width / 2;
        sy /= WINDOW_height / 2;
        sx -= 1;
        sy -= 1;
        xlen /= WINDOW_width / 2;
        ylen /= WINDOW_height / 2;
        glBegin(GL_POLYGON);
        if(color == "red") {
            glColor3d(1.0, 0.0, 0.0);
        } else if(color == "blue") {
            glColor3d(0.0, 0.0, 1.0);
        } else if(color == "green") {
            glColor3d(0.0, 1.0, 0.0);
        }

        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    };
    // 描画のループ

    while(!glfwWindowShouldClose(window1)) {
        // 画面を塗りつぶす
        glClear(GL_COLOR_BUFFER_BIT);
        show(20, 20, 500.0, 660.0,"red");
        show(540, 50, 200, 100,"blue");
        show(540, 190, 200, 100,"blue");
        show(540, 330, 200, 100,"blue");



        // 上記描画した図形を表画面のバッファにスワップする
        glfwSwapBuffers(window1);

        // 受け取ったイベント（キーボードやマウス入力）を処理する
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}