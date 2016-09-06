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
	double dot(Vector i, Vector j);
	Vector cross(Vector i, Vector j); // do i need this?
	friend Vector operator - (const Vector &i, const Vector &j);
	friend Vector operator + (const Vector &i, const Vector &j);
	Vector scalar (const Vector &i, double d);
	void operator = (const Vector &rhs);
	double getX();
	double getY();
	double getZ();

	virtual ~Vector();
private:
	double x;
	double y;
	double z;
};

std::ostream &operator << (std::ostream& sout, const Vector &myVector);

#endif /* VECTOR_H_ */
