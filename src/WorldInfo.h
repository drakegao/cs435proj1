/*
 * WorldInfo.h
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#ifndef WORLDINFO_H_
#define WORLDINFO_H_

#include "Vector.h"
#include "View.h"
#include <cmath>

/* backgroud color */
struct Color {
	double r, g, b;
	Color(){r = g = b =0;}
	Color(double r, double g, double b) {
		this->r = floor(r == 1.0 ? 255 : r * 256);
		this->g = floor(r == 1.0 ? 255 : g * 256);
		this->b = floor(r == 1.0 ? 255 : b * 256);
	}
};

/* fill color */
struct FillColor {
	double r, g, b, kd, ks, shine, T;
	FillColor(){
		r = g = b = kd = ks = shine = T = 0;
	}
	FillColor(double r, double g, double b, double kd, double ks, double shine, double T) {
		this->r = r; this->g = g; this->b = b; this->kd = kd; this->ks = ks; this->shine = shine; this->T = T;
	}
};

class WorldInfo {
public:
	WorldInfo();
	int getHeight();
	int getWidth();
	View* getViewPoint();
	void setHeight(int h);
	void setWidth(int w);
	void setView(View* v);
	Color getBgColor();
	FillColor getFillColor();
	void setBgColor(Color bg);
	void setFillColor(FillColor fill);
	virtual ~WorldInfo();

private:
	Color bgColor;
	FillColor fillColor;
	int hight;
	int width;
	View* view;
};

#endif /* WORLDINFO_H_ */
