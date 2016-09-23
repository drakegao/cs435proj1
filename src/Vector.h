/*
 * Vector.h
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

class Vector {
public:
	Vector();
	Vector(double, double, double);
	Vector(double, double, double, double, double, double);
	double dot(Vector i, Vector j);
	Vector cross(Vector j); // do i need this?
	friend Vector operator - (const Vector &i, const Vector &j);
	friend Vector operator + (const Vector &i, const Vector &j);
	Vector VecDivision (const Vector &i, double t);
	Vector getUnit(Vector i);
	Vector scalar (const Vector &i, double d);
	double getXYZbyIndex(int index);
	double getLength();
	void operator = (const Vector &rhs);
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	double getXN();
	double getYN();
	double getZN();
	void setXN(double);
	void setYN(double);
	void setZN(double);

	virtual ~Vector();
private:
	double x;
	double y;
	double z;
	double xn;
	double yn;
	double zn;
};

std::ostream &operator << (std::ostream& sout, const Vector &myVector);

#endif /* VECTOR_H_ */
