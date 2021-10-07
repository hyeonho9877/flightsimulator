#pragma once
#include "geometry.h"
#include <cmath>
#include <iostream>
using namespace std;

class Ship {
public:
	// ���� ��ġ�� �ٶ󺸴� ������ �Ű������� �޴� ������
	Ship(Point position, Point lookAt);
	// Ű���带 ������ �� �����̴� ���� �����ϴ� �޼ҵ�
	void go(int dir);
	// Ű���带 ������ ���� �����̴� ���� �����ϴ� �޼ҵ�
	void go();

	// Getter
	double getXPos();
	double getYPos();
	double getZPos();
	double getLookAtXPos();
	double getLookAtZPos();
	double getLookAtYPos();
	double getAccel();
	
	// ��ü�� �����̳� ���������� ȸ����Ű�� �޼ҵ�
	void turn(float angle);
	// ��ü�� ���� ������ ���� �Ʒ��� ��ȯ�ϴ� �޼ҵ�
	void upAndDown(float angle);
private:
	// ���� ��ġ
	Point position;
	// ���� ����
	Point lookAt;
	// ������ ���� ���̸� 1, �ڷ� ���� ���̸� -1
	int dir = 0;
	// ��ü�� ���ӵ�
	double accel = 0.0;
	// ���� ������ ������ �ް��ִ����� ���� ����
	bool isInMomentum = false;
};

inline Ship::Ship(Point position, Point lookAt) {
	this->position = position;
	this->lookAt = lookAt;
}

inline void Ship::go(int dir) {
	// ù Ű���� �Է��� ��� �ش� �������� ���� �ʱ�ȭ
	if (this->dir == 0)
		this->dir = dir;

	// ������ �Է°� ���� �Է��� �����ϸ�, ������ ������ ���� �ʴ� ���
	// ����ؼ� ���ӵ��� ������ ��ü�� ��ġ�� ��������
	if (this->dir == dir && !isInMomentum) {
		cout << "Well Driving" << endl;
		isInMomentum = false;
		accel = accel > 0.2 ? 0.2 : accel + 0.002;
		position.x = position.x + this->dir * lookAt.x * accel;
		position.z = position.z + this->dir * lookAt.z * accel;
		position.y = position.y + this->dir * lookAt.y * accel;
	}
	
	// ���� �Է°� ���� �Է��� �ٸ��ų� ������ ������ �޴� ���� ���
	else {
		this->dir = dir;
		isInMomentum = true;

		// ���ӵ��� �����ϰ� ���� ��Ŵ
		accel = accel - 0.02;

		// ���ӵ��� 0���� ū ��� ���� ���� ������ ��� �̵�
		if (accel > 0) {
			cout << "I'm in Momentum" << endl;
			position.x = position.x + -dir * lookAt.x * accel;
			position.z = position.z + -dir * lookAt.z * accel;
			position.y = position.y + -dir * lookAt.y * accel;
		}

		// ���ӵ��� 0 ���ϰ� �� ��� �������� ���
		else {
			cout << "Momentum End" << endl;
			isInMomentum = false;
		}
	}
	
}

inline void Ship::go() {
	// ������ ������ �ް� �ִٸ� ���� ������ �ݴ�������� ����ؼ� �̵�
	if (isInMomentum) {
		position.x = position.x + -this->dir * lookAt.x * accel;
		position.z = position.z + -this->dir * lookAt.z * accel;
		position.y = position.y + -this->dir * lookAt.y * accel;
	}

	// �ݴ��� ���� ���� ������ ��� �̵�
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