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
	for(int i = 0; i < polyguns.size(); i++) {
		delete polyguns[i];
	}
	if(view != NULL) {
		delete view;
	}
}

View* WorldInfo::getViewPoint() {
	return view;
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
