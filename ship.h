#pragma once
#include "geometry.h"
#include <cmath>
#include <iostream>
using namespace std;

class Ship {
public:
	// 현재 위치와 바라보는 방향을 매개변수로 받는 생성자
	Ship(Point position, Point lookAt);
	// 키보드를 눌렀을 때 움직이는 것을 구현하는 메소드
	void go(int dir);
	// 키보드를 떼었을 때도 움직이는 것을 구현하는 메소드
	void go();

	// Getter
	double getXPos();
	double getYPos();
	double getZPos();
	double getLookAtXPos();
	double getLookAtZPos();
	double getLookAtYPos();
	double getAccel();
	
	// 선체를 왼쪽이나 오른쪽으로 회전시키는 메소드
	void turn(float angle);
	// 선체의 진행 방향을 위나 아래로 전환하는 메소드
	void upAndDown(float angle);
private:
	// 현재 위치
	Point position;
	// 보는 방향
	Point lookAt;
	// 앞으로 가는 중이면 1, 뒤로 가는 중이면 -1
	int dir = 0;
	// 선체의 가속도
	double accel = 0.0;
	// 현재 관성의 영향을 받고있는지에 대한 변수
	bool isInMomentum = false;
};

inline Ship::Ship(Point position, Point lookAt) {
	this->position = position;
	this->lookAt = lookAt;
}

inline void Ship::go(int dir) {
	// 첫 키보드 입력인 경우 해당 방향으로 변수 초기화
	if (this->dir == 0)
		this->dir = dir;

	// 이전에 입력과 현재 입력이 동일하며, 관성의 영향을 받지 않는 경우
	// 계속해서 가속도가 붙으며 선체의 위치를 변경해줌
	if (this->dir == dir && !isInMomentum) {
		cout << "Well Driving" << endl;
		isInMomentum = false;
		accel = accel > 0.2 ? 0.2 : accel + 0.002;
		position.x = position.x + this->dir * lookAt.x * accel;
		position.z = position.z + this->dir * lookAt.z * accel;
		position.y = position.y + this->dir * lookAt.y * accel;
	}
	
	// 이전 입력과 현재 입력이 다르거나 관성의 영향을 받는 중인 경우
	else {
		this->dir = dir;
		isInMomentum = true;

		// 가속도를 일정하게 감소 시킴
		accel = accel - 0.02;

		// 가속도가 0보다 큰 경우 이전 진행 방향대로 계속 이동
		if (accel > 0) {
			cout << "I'm in Momentum" << endl;
			position.x = position.x + -dir * lookAt.x * accel;
			position.z = position.z + -dir * lookAt.z * accel;
			position.y = position.y + -dir * lookAt.y * accel;
		}

		// 가속도가 0 이하가 된 경우 관성에서 벗어남
		else {
			cout << "Momentum End" << endl;
			isInMomentum = false;
		}
	}
	
}

inline void Ship::go() {
	// 관성의 영향을 받고 있다면 진행 방향의 반대방향으로 계속해서 이동
	if (isInMomentum) {
		position.x = position.x + -this->dir * lookAt.x * accel;
		position.z = position.z + -this->dir * lookAt.z * accel;
		position.y = position.y + -this->dir * lookAt.y * accel;
	}

	// 반대의 경우는 진행 방향대로 계속 이동
	else {
		if (accel > 0)
			accel = accel - 0.0002 < 0 ? 0 : accel - 0.0002;
		if (accel == 0)
			isInMomentum = false;
		position.x = position.x + this->dir * lookAt.x * accel;
		position.z = position.z + this->dir * lookAt.z * accel;
		position.y = position.y + this->dir * lookAt.y * accel;
	}
}

inline double Ship::getXPos() {
	return position.x;
}

inline double Ship::getYPos() {
	return position.y;
}

inline double Ship::getZPos() {
	return position.z;
}

inline void Ship::turn(float angle) {
	lookAt.x = sin(angle);
	lookAt.z = -cos(angle);
}

inline double Ship::getLookAtXPos() {
	return lookAt.x;
}

inline double Ship::getLookAtZPos() {
	return lookAt.z;
}

inline double Ship::getLookAtYPos() {
	return lookAt.y;
}

inline double Ship::getAccel() {
	return accel;
}

inline void Ship::upAndDown(float angle) {
	lookAt.y = sin(angle);
}