// #include "../include/funcA.hpp"
// Shift+Alt+fで形を整える
// ctrl+sでセーブ
#include <bits/stdc++.h>
#include "../include/GL/glut.h"
using namespace std;
int mouse_click_state = 0;
static int displayFlag = 0;

void display(void) {
    //制御フラグによりいくつかのメソッドorクラスに投げるだけ
	glClearColor(1.0, 1.0, 1.0, 1.0);	// glClear する際の背景色を指定
	glClear(GL_COLOR_BUFFER_BIT);	// カラーバッファを初期化
	if(mouse_click_state != 0) {
		glBegin(GL_TRIANGLES);
			glColor3f(1.0, 0.0, 0.0);	// 赤色
			glVertex2f(0.0, 0.5);

			glColor3f(0.0, 1.0, 0.0);	// 緑色
			glVertex2f(-0.5, -0.5);

			glColor3f(0.0, 0.0, 1.0);	// 青色
			glVertex2f(0.5, -0.5);
		glEnd();
	}

	glFinish();	// 命令の実行
}

// マウスクリックでの処理
void mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON) {
		printf("(%d, %d) で左クリックしました\n", x, y);
		mouse_click_state = 1;
	}
	else if(button == GLUT_RIGHT_BUTTON) {
		printf("(%d, %d) で右クリックしました\n", x, y);
		mouse_click_state = 0;
	}
	display();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);	// GLUTの初期化
	glutInitDisplayMode(GLUT_RGB);	// ディスプレイモードをRGBに設定
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello OpenGL!");
	glutMouseFunc(mouse);	// マウスクリック用のコールバック関数
	glutDisplayFunc(display);	// ディスプレイ用のコールバック関数の設定
	glutMainLoop();	// メインループへ
	return 0;
}