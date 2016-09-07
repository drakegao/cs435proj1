//============================================================================
// Name        : RayTracing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ReadFile.h"

#define PI 3.14159265


using namespace std;
/* cross, AxB = [Ay*Bz + Az*By, Az*Bx + Ax*Bz, Ax*By + Ay*Bx]
 * piont intersection: (p-p0)⋅n=0,l0+l∗t=p
 * t=−(l0−p0)⋅/nl⋅n=(p0-l0)⋅/nl⋅n
 * */
struct Ray {
	// origin
	Vector origin;
	Vector direction;
	// direction
};

int main(int argc, char *argv[]) {
	cout << argc << " " << argv[0] << endl;
	ReadFile readFile;
	readFile.readFile("tetra-3.nff");
	//readFile.readFile(argv[1]);
	WorldInfo* worldInfo = readFile.getWorldInfo();
	vector<Polygun*> polyguns = worldInfo->getPolygun();

	/* for testing view value */
	View* view = worldInfo->getViewPoint();
	/*cout << "FromVec in main: " << view->getFrom() << endl;
	cout << "AtVec in main: " << view->getAt() << endl;
	cout << "UpVec in main: " << view->getUp() << endl;
	cout << "Angle in main: " << view->getAngle() << endl;
	cout << "Hither in main: " << view->getHither() << endl;
	cout << "Res in main: " << view->getWidth() << " " << view->getHeight() << endl;*/

	int H, W;
	H = view->getHeight();
	W = view->getWidth();

	FILE* file = fopen("testing.ppm", "wb");

	fwrite("P6 ", 1, 3, file);
	fwrite("500", 1, 4, file); // width
	fwrite("500", 1, 4, file); // height
	fwrite("255", 1, 4, file);

	Color bgColor = worldInfo->getBgColor();

	unsigned char pixels[H][W][3];

	/**
	 * get coordinates vectors from Eye;
	 */
	Vector eye = view->getFrom();
	Vector up = view->getUp();
	Vector at = view->getAt();
	Vector vecW = worldInfo->getW(eye, at);
	Vector vecU = worldInfo->getV(vecW, up);
	Vector vecV = worldInfo->getV(vecW, vecU);
	/* get unit vectors */
	vecW = vecW.getUnit(vecW);
	vecU = vecU.getUnit(vecU);
	vecV = vecV.getUnit(vecV);

	/* get angle and distance */
	int angle = view->getAngle();
	Vector toCOI = worldInfo->getDistToCOI();
	double unitToCOI = toCOI.getLength();
	double distToCOI = tan((angle / 2) * (PI / 180)) * unitToCOI;
	double left = -distToCOI;
	double bottom = -distToCOI;
	double right = distToCOI;
	double top = distToCOI;


	/* get ray */
	for(int h = 0; h < 3; h++) {
		for(int w = 0; w < 3; w++) {
			/* get scaler, set j: in H dir, i: in W dir*/
			double S = ((h + 0.5) / H) * (right - left) - distToCOI;
			double C = ((w + 0.5) / W) * (top - bottom) - distToCOI;
			Vector scalerU = vecU.scalar(vecV, S);
			Vector scalerV = vecV.scalar(vecV, C);
			Vector scalerW = vecW.scalar(vecW, unitToCOI);

			/* get direction ray */
			Vector dir = scalerU + scalerV - scalerW - eye;

			/* loop through objs */


			/* get ray dir */
			pixels[h][w][0] = bgColor.r;
			pixels[h][w][1] = bgColor.g;
			pixels[h][w][2] = bgColor.b;
		}
	}
	fwrite(pixels, 1, H*W*3, file);

	fclose(file);

	/* testing vector operators */
	Vector v(1,1,1);

/*	Vector eye = view->getFrom();
	Vector up = view->getUp();
	Vector at = view->getAt();
	Vector vecW = worldInfo->getW(eye, at);
	Vector vecU = worldInfo->getV(vecW, up);
	Vector vecV = worldInfo->getV(vecW, vecU);
	 get unit vector
	vecW = vecW.getUnit(vecW);
	vecU = vecU.getUnit(vecU);
	vecV = vecV.getUnit(vecV);
	cout << "vec2: " << vec2 << endl;
	cout << "vecW: " << vecW << endl;
	cout << "vecU: " << vecU << endl;
	cout << "vecV: " << vecV << endl;
	cout << "len: " << dist2 << endl;
	Vector v2 = v.scalar(v, 3);
	cout << v2 << endl;
	*/

	return 0;
}


/*p 3
-1 -0.5 0.5
-1 -1 1
-0.5 -0.5 1
p 3
-1 -0.5 0.5
-1 0 0
-0.5 -0.5 0
p 3
-0.5 0 0.5
-0.5 -0.5 0
-1 0 0
p 3
-0.5 -0.5 0
-0.5 0 0.5
-1 -0.5 0.5
p 3
-1 0 0
-1 -0.5 0.5
-0.5 0 0.5
p 3
-0.5 -1 0.5
-0.5 -0.5 0
0 -1 0
p 3
0 -0.5 0.5
0 -1 0
-0.5 -0.5 0
p 3
0 -1 0
0 -0.5 0.5
-0.5 -1 0.5
p 3
-0.5 -0.5 0
-0.5 -1 0.5
0 -0.5 0.5
p 3
-0.5 -0.5 1
-0.5 0 0.5
0 -0.5 0.5
p 3
0 0 1
0 -0.5 0.5
-0.5 0 0.5
p 3
0 -0.5 0.5
0 0 1
-0.5 -0.5 1
p 3
-0.5 0 0.5
-0.5 -0.5 1
0 0 1
p 3
-1 0 0
-1 0.5 -0.5
-0.5 0 -0.5
p 3
-0.5 0.5 0
-0.5 0 -0.5
-1 0.5 -0.5
p 3
-0.5 0 -0.5
-0.5 0.5 0
-1 0 0
p 3
-1 0.5 -0.5
-1 0 0
-0.5 0.5 0
p 3
-1 0.5 -0.5
-1 1 -1
-0.5 0.5 -1
p 3
-0.5 1 -0.5
-0.5 0.5 -1
-1 1 -1
p 3
-0.5 0.5 -1
-0.5 1 -0.5
-1 0.5 -0.5
p 3
-1 1 -1
-1 0.5 -0.5
-0.5 1 -0.5
p 3
-0.5 0 -0.5
-0.5 0.5 -1
0 0 -1
p 3
0 0.5 -0.5
0 0 -1
-0.5 0.5 -1
p 3
0 0 -1
0 0.5 -0.5
-0.5 0 -0.5
p 3
-0.5 0.5 -1
-0.5 0 -0.5
0 0.5 -0.5
p 3
-0.5 0.5 0
-0.5 1 -0.5
0 0.5 -0.5
p 3
0 1 0
0 0.5 -0.5
-0.5 1 -0.5
p 3
0 0.5 -0.5
0 1 0
-0.5 0.5 0
p 3
-0.5 1 -0.5
-0.5 0.5 0
0 1 0
p 3
0 -1 0
0 -0.5 -0.5
0.5 -1 -0.5
p 3
0.5 -0.5 0
0.5 -1 -0.5
0 -0.5 -0.5
p 3
0.5 -1 -0.5
0.5 -0.5 0
0 -1 0
p 3
0 -0.5 -0.5
0 -1 0
0.5 -0.5 0
p 3
0 -0.5 -0.5
0 0 -1
0.5 -0.5 -1
p 3
0.5 0 -0.5
0.5 -0.5 -1
0 0 -1
p 3
0.5 -0.5 -1
0.5 0 -0.5
0 -0.5 -0.5
p 3
0 0 -1
0 -0.5 -0.5
0.5 0 -0.5
p 3
0.5 -1 -0.5
0.5 -0.5 -1
1 -1 -1
p 3
1 -0.5 -0.5
1 -1 -1
0.5 -0.5 -1
p 3
1 -1 -1
1 -0.5 -0.5
0.5 -1 -0.5
p 3
0.5 -0.5 -1
0.5 -1 -0.5
1 -0.5 -0.5
p 3
0.5 -0.5 0
0.5 0 -0.5
1 -0.5 -0.5
p 3
1 0 0
1 -0.5 -0.5
0.5 0 -0.5
p 3
1 -0.5 -0.5
1 0 0
0.5 -0.5 0
p 3
0.5 0 -0.5
0.5 -0.5 0
1 0 0
p 3
0 0 1
0 0.5 0.5
0.5 0 0.5
p 3
0.5 0.5 1
0.5 0 0.5
0 0.5 0.5
p 3
0.5 0 0.5
0.5 0.5 1
0 0 1
p 3
0 0.5 0.5
0 0 1
0.5 0.5 1
p 3
0 0.5 0.5
0 1 0
0.5 0.5 0
p 3
0.5 1 0.5
0.5 0.5 0
0 1 0
p 3
0.5 0.5 0
0.5 1 0.5
0 0.5 0.5
p 3
0 1 0
0 0.5 0.5
0.5 1 0.5
p 3
0.5 0 0.5
0.5 0.5 0
1 0 0
p 3
1 0.5 0.5
1 0 0
0.5 0.5 0
p 3
1 0 0
1 0.5 0.5
0.5 0 0.5
p 3
0.5 0.5 0
0.5 0 0.5
1 0.5 0.5
p 3
0.5 0.5 1
0.5 1 0.5
1 0.5 0.5
p 3
1 1 1
1 0.5 0.5
0.5 1 0.5
p 3
1 0.5 0.5
1 1 1
0.5 0.5 1
p 3
0.5 1 0.5
0.5 0.5 1
1 1 1*/
