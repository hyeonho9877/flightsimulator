#include <gl/glut.h>
#include <iostream>
#include "ship.h"
#include "landscape.h"
#include "cockpit.h"
using namespace std;

#define _WINDOW_WIDTH 1280
#define _WINDOW_HEIGHT 740

// ���÷��� �ݹ� �Լ�
void display();
// reshape �ݹ� �Լ�
void reshape(int width, int height);
// Ű���� �ݹ� �Լ�
void keyboard(unsigned char key, int x, int y);
// ���� ȿ�� ���� �Լ�
void enableLighting();
// �ܼ� ��� �Լ�
void printPosToConsole();
// Ÿ�̸� �ݹ� �Լ�
void timer(int value);

// �þ߰�, ȭ���, y�� �þ߰�
static float angle = 0.0, ratio, angleY = 0.0;
// ī�޶� �ʱ� ��ġ
static float x = 0.0f, y = 10.0f, z = 5.0f;
// ī�޶� �ʱ� �ٶ󺸴� ��ġ
static float lx = 0.0f, ly = 0.0f, lz = -1.0f;

// �ʿ��� ��ü ����
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
* w�� ������ ����
* s�� ������ ����
* d�� ������ �þ߸� ���������� ȸ��
* a�� ������ �þ߸� �������� ȸ��
* 8�� ������ �þ߸� ���� ȸ��
* 2�� ������ �þ߸� �Ʒ��� ȸ��
* c�� ������ ������ ��ġ�� ����
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
	// ȭ�� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (float)GLUT_SCREEN_WIDTH / GLUT_SCREEN_HEIGHT;
	gluPerspective(45, ratio, 0.1, 300);

	printPosToConsole();

	// ���� ����
	gluLookAt(ship.getXPos(), ship.getYPos(), ship.getZPos(),
		ship.getXPos()+ship.getLookAtXPos(), ship.getYPos()+ship.getLookAtYPos(), ship.getZPos()+ship.getLookAtZPos(),
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// ��� �׸���
	landscape.drawLand();
	// ���� �׸���
	glCallList(landscape.getBuildingLists());
	// ��ġ�� ���� �ִٸ� �þ��� �������� �׿� �°� ����
	if(!cockpit.getHatchOpened())
		cockpit.draw();

	// ���� ���۸��� ���� �Լ� ȣ��
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

	// ���� ��ġ ����
	GLfloat lightpos[] = { 50,50,200, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	// ������ Ambient�� ����
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