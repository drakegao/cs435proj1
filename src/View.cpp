/*
 * View.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: drake
 */

#include "View.h"

using namespace std;
View::View() {
	// TODO Auto-generated constructor stub
	angle = height = width = 0;
}

View::~View() {
	// TODO Auto-generated destructor stub
	cout << "View is destroyed now" << endl;
}

void View::setFrom(Vector f) {
	this->from = f;
}
void View::setAt(Vector a) {
	this->at = a;
}
void View::setUp(Vector up) {
	this->up = up;
}
void View::setAngle(int angle) {
	this->angle = angle;
}
void View::setWidth(int w) {
	this->width = w;
}
void View::setHeight(int h) {
	this->height = h;
}
Vector View::getFrom() {
	return this->from;
}
Vector View::getAt() {
	return this->at;
}
Vector View::getUp() {
	return this->up;
}
int View::getAngle() {
	return this->angle;
}
int View::getWidth() {
	return this->width;
}
int View::getHeight() {
	return this->height;
}

void View::setHither(int hither) {
	this->hither = hither;
}

int View::getHither() {
	return this->hither;
}
