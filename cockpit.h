#ifndef COCKPIT_H_
#define COCKPIT_H_

#include <GL/glut.h>

class Cockpit {
    // ������ ���÷��� ����Ʈ ���̵�
    int cockpitID;
    // ���� ��ġ�� ���� ����
    bool hatchOpened = false;
public:
    // ���÷��� ����Ʈ ����
    void create();
    // ����Ʈ ������� ���� �׸��� ����
    void draw();
    // ��ġ ����
    void openHatch();
    // ��ġ �ݱ�
    void closeHatch();
    
    // Getter
    bool getHatchOpened();
};

void Cockpit::create() {
    // �� ���� ����Ʈ ����
    cockpitID = glGenLists(1);
    glNewList(cockpitID, GL_COMPILE);

    // ������ Ư���� �°� ������Ʈ�� �׸��� ����
    // �ʿ��� ���� ����
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);

    // ���� ����
    glColor4f(0.93, 1, 1, 0.3);

    // ȭ���� �� ä�� �簢���� �׸�
    glBegin(GL_QUADS);
    glVertex3f(-1, 10, 0);
    glVertex3f(-1, -10, 0);
    glVertex3f(1, -10, 0);
    glVertex3f(1, 10, 0);
    glEnd();

    // ���� ����
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glEndList();
}

inline void Cockpit::draw() {
    // ������ ������� ����Ʈ�� �ҷ��� ������Ʈ�� �׸�
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glCallList(cockpitID);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

inline void Cockpit::openHatch() {
    hatchOpened = true;
}

inline void Cockpit::closeHatch()
{
    hatchOpened = false;
}

inline bool Cockpit::getHatchOpened() {
    return hatchOpened;
}

#endif