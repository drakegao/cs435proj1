/*
 * Vector.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#include "Vector.h"
#include <iostream>
#include <cmath>

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


/**
 * get length
 */
double Vector::getLength() {
	double x, y, z;
	x = this->x;
	y = this->y;
	z = this->z;
	double distSqr = pow(x, 2) + pow(y, 2) + pow(z, 2);
	double length = std::sqrt(distSqr);
	return length;
}

/**
 * for vector addition
 */
Vector operator + (const Vector &i, const Vector &j) {
	return Vector(i.x + j.x, i.y + j.y, i.z + j.z);
}

// vector subtraction
Vector operator - (const Vector &i, const Vector &j) {
	return Vector(i.x - j.x, i.y - j.y, i.z - j.z);
}

/**
 * for vector division
 */
Vector Vector::VecDivision(const Vector &i, double t) {
	double u, v, w;
	u = i.x / t;
	v = i.y / t;
	w = i.z / t;
	return Vector(u, v, w);
}

/**
 * get unit vector
 */
Vector Vector::getUnit(Vector i) {

	double length = i.getLength();
	Vector unitW = i.VecDivision(i, length);
	return unitW;
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

/**
 * for cross product
 */
Vector Vector::cross(Vector j) {
	double x, y, z;
	x = this->getY() * j.getZ() - this->getZ() * j.getY();
	y = this->getZ() * j.getX() - this->getX() * j.getZ();
	z = this->getX() * j.getY() - this->getY() * j.getX();
	return Vector(x, y, z);
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
