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
#include <vector>

using namespace std;
/* backgroud color */
struct Color {
	double r, g, b;
	Color(){r = g = b =0;}
	Color(double r, double g, double b) {
		this->r = floor(r == 1.0 ? 255 : r * 256);
		this->g = floor(g == 1.0 ? 255 : g * 256);
		this->b = floor(b == 1.0 ? 255 : b * 256);
	}
};

/* polygun struct */
struct Polygun {
	vector<Vector> polyEdges;
};

struct Ray {
	// origin
	Vector origin;
	Vector direction;
	// direction

	Ray(Vector o, Vector d) {
		origin = o;
		direction = d;
	}
};

/* fill color */
struct FillColor {
	double r, g, b, kd, ks, shine, T;
	FillColor(){
		r = g = b = kd = ks = shine = T = 0;
	}
	FillColor(double r, double g, double b, double kd, double ks, double shine, double T) {
		this->r = floor(r == 1.0 ? 255 : r * 256);
		this->g = floor(g == 1.0 ? 255 : g * 256);
		this->b = floor(b == 1.0 ? 255 : b * 256);

		this->kd = kd; this->ks = ks; this->shine = shine; this->T = T;
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
	void setPolygun(vector<Polygun* > polyguns);
	Color getBgColor();
	FillColor getFillColor();
	vector<Polygun* > getPolygun();

	/* get v, u, w origin from eye */
	Vector getW(Vector from, Vector at);
	Vector getU(Vector W, Vector up);
	Vector getV(Vector W, Vector U);
	Vector getDistToCOI();
	bool isIntersect(Polygun* p, Ray r);
	void setBgColor(Color bg);
	void setFillColor(FillColor fill);
	virtual ~WorldInfo();

private:
	Color bgColor;
	FillColor fillColor;
	vector<Polygun* > polyguns;
	int hight;
	int width;
	View* view;
};

#endif /* WORLDINFO_H_ */
