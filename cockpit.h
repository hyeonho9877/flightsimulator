#ifndef COCKPIT_H_
#define COCKPIT_H_

#include <GL/glut.h>

class Cockpit {
    // 콕핏의 디스플레이 리스트 아이디
    int cockpitID;
    // 현재 해치의 개폐 여부
    bool hatchOpened = false;
public:
    // 디스플레이 리스트 생성
    void create();
    // 리스트 기반으로 실제 그리기 실행
    void draw();
    // 해치 오픈
    void openHatch();
    // 해치 닫기
    void closeHatch();
    
    // Getter
    bool getHatchOpened();
};

void Cockpit::create() {
    // 한 개의 리스트 생성
    cockpitID = glGenLists(1);
    glNewList(cockpitID, GL_COMPILE);

    // 콕핏의 특성에 맞게 오브젝트를 그리기 위해
    // 필요한 설정 조작
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);

    // 색깔 설정
    glColor4f(0.93, 1, 1, 0.3);

    // 화면을 꽉 채울 사각형을 그림
    glBegin(GL_QUADS);
    glVertex3f(-1, 10, 0);
    glVertex3f(-1, -10, 0);
    glVertex3f(1, -10, 0);
    glVertex3f(1, 10, 0);
    glEnd();

    // 설정 복원
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glEndList();
}

inline void Cockpit::draw() {
    // 기존에 만들었던 리스트를 불러와 오브젝트를 그림
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