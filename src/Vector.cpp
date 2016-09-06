/*
 * Vector.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#include "Vector.h"
#include <iostream>

using namespace std;
Vector::Vector() {
	// TODO Auto-generated constructor stub
	x = y = z = 0;
}

Vector::Vector(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector::getX() {
	return this->x;
}

double Vector::getY() {
	return this->y;
}

double Vector::getZ() {
	return this->z;
}

// return a dot product
double Vector::dot(Vector i, Vector j) {
	return (i.getX() * j.getX() + i.getY() * j.getY() + i.getZ() * i.getZ());
}

Vector::~Vector() {
	// TODO Auto-generated destructor stub
}

// vector subtraction
Vector operator - (const Vector &i, const Vector &j) {
	return Vector(i.x - j.x, i.y - j.y, i.z - j.z);
}

/**
 * for vector addition
 */
Vector operator + (const Vector &i, const Vector &j) {
	return Vector(i.x + j.x, i.y + j.y, i.z + j.z);
}

/*
 * for scalar vector
 */
Vector Vector::scalar (const Vector &i, double d) {
	double x = i.x * d;
	double y = i.y * d;
	double z = i.z * d;
	Vector newVec(x, y, z);
	return newVec;
}

void Vector::operator = (const Vector &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}

ostream & operator << (ostream& sout, const Vector &vec) {
	Vector myVec = vec;
	double posX = myVec.getX();
	double posY = myVec.getY();
	double posZ = myVec.getZ();
	sout << posX << " " << posY << " " << posZ << endl;
	return sout;
}
