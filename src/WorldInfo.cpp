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

/**
 * get matrix
 */
vector<Vector> WorldInfo::getMatrix(Polygun p, Vector dir) {
	Vector v0= p.polyEdges[0];
	Vector v1 = p.polyEdges[1];
	Vector v2 = p.polyEdges[2];
	Vector v1v0 = v1 - v0;
	Vector v2v0 = v2 - v0;
	Vector dirReverse = dir.scalar(dir, -1);
	vector<Vector> matrix;
	matrix.push_back(v1v0);
	matrix.push_back(v2v0);
	matrix.push_back(dirReverse);

	vector<Vector> result;
	return result;
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
