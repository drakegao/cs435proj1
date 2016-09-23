/*
 * WorldInfo.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#include "WorldInfo.h"
#include <iostream>
#include <vector>

using namespace std;
WorldInfo::WorldInfo() {
	// TODO Auto-generated constructor stub
    view = NULL;
}

WorldInfo::~WorldInfo() {
	// TODO Auto-generated destructor stub
	std::cout << "worldInfo is gone" << endl;
	for(unsigned int i = 0; i < polyguns.size(); i++) {
		delete polyguns[i];
	}
	if(view != NULL) {
		delete view;
	}
}

/**
 * get the W vector: eye - lookat
 */
Vector WorldInfo::getW(Vector eye, Vector at) {
	Vector W = eye - at;
	return W;
}

Vector WorldInfo::getU(Vector W, Vector Up) {
	Vector U = W.cross(Up);
	return U;
}

Vector WorldInfo::getV(Vector W, Vector U) {

	Vector V = W.cross(U);
	return V;
}

View* WorldInfo::getViewPoint() {
	return view;
}

/* get distance */
Vector WorldInfo::getDistToCOI() {
	Vector COI = this->getViewPoint()->getAt() - this->getViewPoint()->getFrom();
	return COI;
}
void WorldInfo::setView(View* v) {
	this->view = v;
}

Color WorldInfo::getBgColor() {
	return this->bgColor;
}

FillColor WorldInfo::getFillColor() {
	return this->fillColor;
}

int WorldInfo::getHeight() {
	return this->hight;
}

int WorldInfo::getWidth() {
	return this->width;
}

vector<Polygun* > WorldInfo::getPolygun() {
	return this->polyguns;
}

int WorldInfo::getSize() {
	return this->size;
}

void WorldInfo::setSize(int size) {
	this->size = size;
}

/**
 * detecting intersect
 */
bool WorldInfo::isIntersect(Polygun* p, Ray ray, Vector& pHit, Vector& sNormal) {

	Vector ev0 = p->polyEdges[0] - ray.origin;
	double distVec[3] = {0};
	for(int i = 0; i < 3; i++) {
		distVec[i] = ev0.getXYZbyIndex(i);
	}
	// get two edegs
	Vector v0v1 = p->polyEdges[0] - p->polyEdges[1];
	Vector v0v2 = p->polyEdges[0] - p->polyEdges[2];

	// form the matrix[v0-v1, v0-v2, ray.direction]
	double matrix[3][3] = {0};
	for(int col = 0; col < 3; col++) {
		Vector temp(0,0,0);
		if(col == 0) {
			temp = v0v1;
		} else if(col == 1) {
			temp = v0v2;
		} else if(col == 2){
			temp = ray.direction;
		}
		for(int row = 0; row < 3; row++) {
			matrix[row][col] = temp.getXYZbyIndex(row);
		}
	}

	// try to find inverse of this matrix
	 /* 1, 1/get determinant,
	 * 2, find inverse
	 * 3, inverse of Matrix multiply ev0 vector
	 * 4, determine is ray intersects (0 < x < 1, 0 < y < 1; 0 < x + y < 1, t > 0)
	 */

	/* determinant */
	double det = 0;
	for(int i = 0; i < 3; i++) {
		det += matrix[0][i] * (matrix[1][(i+1) % 3] * matrix[2][(i+2) % 3] - matrix[1][(i+2) % 3] * matrix[2][(i+1) % 3]);
	}

	if(det == 0) {
		return false;
	}

	/* inverse matrix */
	double matrixT[3][3] = {0};
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			double k = ((matrix[(i + 1) % 3][(j + 1) % 3] * matrix[(i + 2) % 3][(j + 2) % 3]) - (matrix[(i + 1) % 3][(j + 2) % 3] * matrix[(i + 2)%3][(j + 1)%3]))/ det;
			matrixT[j][i] = k;
		}
	}

	double res[3] = {0};
	for(int i = 0; i < 3; i++) {
		res[i] = matrixT[i][0] *  distVec[0] + matrixT[i][1] * distVec[1] + matrixT[i][2] * distVec[2];
	}

	double alpha, beta, t;

	alpha = res[0];
	beta = res[1];
	t = res[2];
	if(t < 0) {
		return false;
	}

	bool isIntersect;
	if((alpha > 0 && alpha < 1) && (beta > 0 && beta < 1 - alpha) && t > 0) {
		Vector scalarV = scalarV.scalar(ray.direction, t);
		pHit = ray.origin + scalarV;

		/* get the surface normal of this polygun */
		sNormal = v0v1.cross(v0v2);
		isIntersect = true;
	} else {
		isIntersect = false;
	}

	return isIntersect;

}

Color WorldInfo::trace(Ray ray) {
	/* get the hit point */
	Vector pHit(0, 0, 0);
	Vector sNormal(0, 0, 0);
	Polygun* P = 0;
	double closestHit = 9999;

	for(unsigned int k = 0; k < polyguns.size(); k++) {
		bool touch = false;
		// testing every polygun in current pixel
		Polygun* p = polyguns[k];
		touch = isIntersect(p, ray, pHit, sNormal);

		if(touch) {
			double dist = pHit.getLength();
			if(dist < closestHit) {
				closestHit = dist;
				P = p;
				/* for the proj1 only */
				break;
			}

		}
	}
	Color color(0, 0, 0);
	if(P) {
		double r = P->fillColor.r;
		double g = P->fillColor.g;
		double b = P->fillColor.b;

		color.r = floor(r == 1.0 ? 255 : r * 256);
		color.g = floor(g == 1.0 ? 255 : g * 256);
		color.b = floor(b == 1.0 ? 255 : b * 256);

	} else {
		color.r = floor(this->bgColor.r == 1.0 ? 255 : this->bgColor.r * 256);
		color.g = floor(this->bgColor.g == 1.0 ? 255 : this->bgColor.g * 256);
		color.b = floor(this->bgColor.b == 1.0 ? 255 : this->bgColor.b * 256);
	}
	return color;
}

void WorldInfo::setHeight(int h) {
	this->hight = h;
}

void WorldInfo::setWidth(int w) {
	this->width = w;
}

void WorldInfo::setBgColor(Color bg) {
	this->bgColor = bg;
}

void WorldInfo::setFillColor(FillColor fill) {
	this->fillColor = fill;
}

void WorldInfo::setPolygun(vector<Polygun* > polyguns) {
	this->polyguns = polyguns;
}
