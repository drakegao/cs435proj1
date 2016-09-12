//============================================================================
// Name        : RayTracing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "ReadFile.h"
#include "Testing.h"

#define PI 3.14159265

using namespace std;
int main(int argc, char *argv[]) {
	cout << argc << " " << argv[0] << endl;
	ReadFile readFile;
	readFile.readFile("tetra-3.nff");
	//readFile.readFile(argv[1]);
	WorldInfo* worldInfo = readFile.getWorldInfo();
	// testing passed, polyguns exists
	vector<Polygun*> polyguns = worldInfo->getPolygun();

	/* for testing view value */
	View* view = worldInfo->getViewPoint();
	cout << "FromVec in main: " << view->getFrom() << endl;
	cout << "AtVec in main: " << view->getAt() << endl;
	cout << "UpVec in main: " << view->getUp() << endl;
	cout << "Angle in main: " << view->getAngle() << endl;
	cout << "Hither in main: " << view->getHither() << endl;
	cout << "Res in main: " << view->getWidth() << " " << view->getHeight() << endl;

	int H, W;
	H = view->getHeight();
	W = view->getWidth();

	FILE* file = fopen("testing.ppm", "wb");

	/*fwrite("P6 ", 1, 3, file);
	fwrite(&w, 1, 4, file); // width
	fwrite(&h, 1, 4, file); // height
	fwrite("255", 1, 4, file);*/

	fprintf(file, "P6\n%d %d\n%d\n", W, H, 255);

	Color bgColor = worldInfo->getBgColor();
	FillColor fillColor = worldInfo->getFillColor();

	unsigned char pixels[H][W][3];

	/**
	 * get coordinates vectors from Eye;
	 */
	Vector eye = view->getFrom();
	//eye = eye.getUnit(eye);
	Vector up = view->getUp();
	Vector at = view->getAt();
	Vector vecW = worldInfo->getW(eye, at);

	// get distance focal length
	double d = vecW.getLength();
	Vector vecU = worldInfo->getU(vecW, up);
	Vector vecV = worldInfo->getV(vecW, vecU);
	/* get unit vectors */
	vecW = vecW.getUnit(vecW);
	vecU = vecU.getUnit(vecU);
	vecV = vecV.getUnit(vecV);

	/* get angle and distance */
	int angle = view->getAngle();
	double distToCOI = tan((angle / 2) * (PI / 180)) * d;
	double left = -distToCOI;
	double bottom = -distToCOI;
	double right = distToCOI;
	double top = distToCOI;

	/* get ray */
	for(int h = 0; h < H; h++) {
		double C = ((h + 0.5) / H) * (top - bottom) - distToCOI;
		for(int w = 0; w < W; w++) {
			// fill out background first
			pixels[h][w][0] = bgColor.r;
			pixels[h][w][1] = bgColor.g;
			pixels[h][w][2] = bgColor.b;

			/* get scaler, set j: in H dir, i: in W dir*/
			double S = ((w + 0.5) / W) * (right - left) - distToCOI;
			Vector scalerU = scalerU.scalar(vecU, S);
			Vector scalerV = scalerV.scalar(vecV, C);
			Vector scalerW = scalerW.scalar(vecW, -d);

			/* get direction ray */
			Vector dir = scalerW + scalerU + scalerV;
			//Vector dir(0,0,1);
			Ray ray(eye, dir);

			/* loop through objs */
			for(unsigned int k = 0; k < polyguns.size(); k++) {
				bool touch = false;
				// testing every polygun in current pixel
				Polygun* p = polyguns[k];
				touch = worldInfo->isIntersect(p, ray);
				if(touch) {
					pixels[h][w][0] = fillColor.r;
					pixels[h][w][1] = fillColor.g;
					pixels[h][w][2] = fillColor.b;
					// so far no checking closest distance
					break;
				}
			}

		}
	}
	fwrite(pixels, 1, H*W*3, file);

	fclose(file);

	/*// testing
	Testing test;
	// print all read polyguns
	test.printPolyguns(polyguns);
	// matrix
	Vector v0 = polyguns[0]->polyEdges[0];
	Vector v1 = polyguns[0]->polyEdges[1];
	Vector v2 = polyguns[0]->polyEdges[2];
	Vector dir = view->getAt() - view->getFrom();
	test.getMatrix(v0, v1, v2, dir);*/

	return 0;
}
