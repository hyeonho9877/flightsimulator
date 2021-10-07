#pragma once
#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <GL/glut.h>
#include <random>
#include <iostream>
#include <algorithm>

class Landscape {
public:
	// ���θ� �׸��� �޼ҵ�
	void drawLand();
	// ������ �׸��� �޼ҵ�
	void drawBuilding();
	// Getter
	int getBuildingLists();
private:
	// ������ ���÷��� ����Ʈ
	int buildingID;
};

inline void Landscape::drawLand() {
	// ������ ũ���� ���� �ʵ� ����
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor3f(0.77, 0.53, 0.07);
	glVertex3f(5, 0, 5);
	glVertex3f(5, 0, -100);
	glVertex3f(-100, 0, -100);
	glVertex3f(-100, 0, 5);
	glEnd();
	glEnable(GL_LIGHTING);
}

inline void Landscape::drawBuilding() {
	glDisable(GL_DEPTH_TEST);
	buildingID = glGenLists(1);
	glNewList(buildingID,GL_COMPILE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// ���� �ٸ� ���� ���̸� ���� �ǹ� ����
	for (int i = 1; i < 95; i += 10) {
		for (int j = 1; j < 95; j += 10) {
			glPushMatrix();
			glColor3f(0.5, 0.5, 0.5);
			int width = std::max(rand() % 3, 1);
			int height = std::max(rand() % 15, 4);
			glTranslatef(-0.5 * i, height/2, -0.5 * j);
			glScalef(width, height, 1);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
	glEndList();
	glEnable(GL_DEPTH_TEST);
}

inline int Landscape::getBuildingLists() {
	return buildingID;
}
#endif