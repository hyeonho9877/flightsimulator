#include <gl/glut.h>
#include <iostream>
#include "ship.h"
#include "landscape.h"
#include "cockpit.h"
using namespace std;

#define _WINDOW_WIDTH 1280
#define _WINDOW_HEIGHT 740

// 디스플레이 콜백 함수
void display();
// reshape 콜백 함수
void reshape(int width, int height);
// 키보드 콜백 함수
void keyboard(unsigned char key, int x, int y);
// 광원 효과 설정 함수
void enableLighting();
// 콘솔 출력 함수
void printPosToConsole();
// 타이머 콜백 함수
void timer(int value);

// 시야각, 화면비, y축 시야각
static float angle = 0.0, ratio, angleY = 0.0;
// 카메라 초기 위치
static float x = 0.0f, y = 10.0f, z = 5.0f;
// 카메라 초기 바라보는 위치
static float lx = 0.0f, ly = 0.0f, lz = -1.0f;

// 필요한 객체 선언
static Ship ship(Point(x,y,z), Point(lx,ly,lz));
static Landscape landscape;
static Cockpit cockpit;

void timer(int value) {
	ship.go();
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 1);
}

void printPosToConsole() {
	cout << "xpos " << ship.getXPos() << endl;
	cout << "ypos " << ship.getYPos() << endl;
	cout << "zpos " << ship.getZPos() << endl;
	cout << "LookAtXpos " << ship.getXPos() + ship.getLookAtXPos() << endl;
	cout << "LookAtYpos " << ship.getYPos() + ship.getLookAtYPos() << endl;
	cout << "LookAtZpos " << ship.getZPos() + ship.getLookAtZPos() << endl;
	cout << "Accel" << ship.getAccel() << endl;
	cout << endl;
}

/*
* w를 누르면 전진
* s를 누르면 후진
* d를 누르면 시야를 오른쪽으로 회전
* a를 누르면 시야를 왼쪽으로 회전
* 8을 누르면 시야를 위로 회전
* 2를 누르면 시야를 아래로 회전
* c를 누르면 콕핏의 해치를 개폐
*/
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		ship.go(1);
		break;
	case 's':
		ship.go(-1);
		break;
	case 'd':
		angle += 0.1;
		ship.turn(angle);
		break;
	case 'a':
		angle -= 0.1;
		ship.turn(angle);
		break;
	case '8':
		angleY += 0.1;
		ship.upAndDown(angleY);
		break;
	case '2':
		angleY -= 0.1;
		ship.upAndDown(angleY);
		break;
	case 'c':
		if (cockpit.getHatchOpened())
			cockpit.closeHatch();
		else
			cockpit.openHatch();
	default:
		break;
	}

	glutPostRedisplay();
}

void display() {
	// 화면 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (float)GLUT_SCREEN_WIDTH / GLUT_SCREEN_HEIGHT;
	gluPerspective(45, ratio, 0.1, 300);

	printPosToConsole();

	// 시점 설정
	gluLookAt(ship.getXPos(), ship.getYPos(), ship.getZPos(),
		ship.getXPos()+ship.getLookAtXPos(), ship.getYPos()+ship.getLookAtYPos(), ship.getZPos()+ship.getLookAtZPos(),
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// 배경 그리기
	landscape.drawLand();
	// 빌딩 그리기
	glCallList(landscape.getBuildingLists());
	// 해치가 닫혀 있다면 시야의 불투명도를 그에 맞게 조정
	if(!cockpit.getHatchOpened())
		cockpit.draw();

	// 더블 버퍼링을 위한 함수 호출
	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0.52, 0.8, 0.97, 1.0);
	gluPerspective(45, (float) width / height, 0.1, 100);
}

void enableLighting() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_FACE, GL_AMBIENT);
	glMateriali(GL_FRONT, GL_SHININESS, 3);

	// 광원 위치 설정
	GLfloat lightpos[] = { 50,50,200, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	// 광원을 Ambient로 설정
	GLfloat ambient[] = { 0.5,0.5,0.5,0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutCreateWindow("title");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000 / 60, timer, 1);
	landscape.drawBuilding();
	cockpit.create();
	enableLighting();
	glutMainLoop();
	return 0;
}