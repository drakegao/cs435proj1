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

/* fill color */
struct FillColor {
	double r, g, b, kd, ks, shine, T, index;
	FillColor(){
		r = g = b = kd = ks = shine = T = index = 0;
	}
	FillColor(double r, double g, double b, double kd, double ks, double shine, double T, double index) {
		this->r = r;//floor(r == 1.0 ? 255 : r * 256);
		this->g = g;//floor(g == 1.0 ? 255 : g * 256);
		this->b = b;//floor(b == 1.0 ? 255 : b * 256);

		this->kd = kd; this->ks = ks; this->shine = shine; this->T = T, this->index = index;
	}
};

/* backgroud color */
struct Color {
	double r, g, b;
	Color(){r = g = b =0;}
	Color(double r, double g, double b) {
		this->r = r;//floor(r == 1.0 ? 255 : r * 256);
		this->g = g;//floor(g == 1.0 ? 255 : g * 256);
		this->b = b;//floor(b == 1.0 ? 255 : b * 256);
	}
};

/* light */
struct Light {
	Vector light;
	Light(){};
	Light(Vector light) {
		this->light = light;
	}
};

/* polygun struct */
struct Polygun {
	vector<Vector> polyEdges;
	FillColor fillColor;
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

/* sphere struct */
struct Sphere {
	Vector center;
	double r;
	Sphere(Vector center, double r) {
		this->center = center;
		this->r = r;
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
	void setSize(int);
	Color getBgColor();
	FillColor getFillColor();
	vector<Polygun* > getPolygun();

	/* get v, u, w origin from eye */
	Vector getW(Vector from, Vector at);
	Vector getU(Vector W, Vector up);
	Vector getV(Vector W, Vector U);
	Vector getDistToCOI();
	int getSize();
	bool isIntersect(Polygun* p, Ray r, Vector& pHit, Vector& sNormal);
	Color trace(Ray r);
	void setBgColor(Color bg);
	void setFillColor(FillColor fill);
	Light light;
	virtual ~WorldInfo();

private:
	Color bgColor;
	FillColor fillColor;
	vector<Polygun* > polyguns;
	int hight;
	int width;
	int size;
	View* view;
};

#endif /* WORLDINFO_H_ */
