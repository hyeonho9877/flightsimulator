#pragma once
class Point;
class Vector;

class  Point
{
public:
	double x, y, z;
	Point();
	Point(double x, double y, double z);
private:

};

 Point:: Point(double x, double y, double z){
	 this->x = x;
	 this->y = y;
	 this->z = z;
}

 Point::Point() {
	 this->x = 0;
	 this->y = 0;
	 this->z = 0;
 }

 class Vector
 {
 public:
	 Vector();
	 Vector(double x, double y, double z);
 private:
	 double x, y, z;
 };

 inline Vector::Vector()
 {
	 this->x = 0;
	 this->y = 0;
	 this->z = 0;
 }
 inline Vector::Vector(double x, double y, double z) {
	 this->x = x;
	 this->y = y;
	 this->z = z;
 }