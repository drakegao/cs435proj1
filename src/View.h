/*
 * View.h
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "Vector.h"

class View {
public:
	View();
	virtual ~View();
	void setFrom(Vector f);
	void setHither(int hither);
	void setAt(Vector a);
	void setUp(Vector up);
	void setAngle(int angle);
	void setWidth(int w);
	void setHeight(int h);
	Vector getFrom();
	Vector getAt();
	Vector getUp();
	int getAngle();
	int getWidth();
	int getHeight();
	int getHither();

private:
	Vector from, at, up;
	int angle;
	int hither;
	int width;
	int height;
};

#endif /* VIEW_H_ */
