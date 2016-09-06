//============================================================================
// Name        : RayTracing.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ReadFile.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << argc << " " << argv[0] << endl;
	ReadFile readFile;
	readFile.readFile("tetra-3.nff");
	//readFile.readFile(argv[1]);
	WorldInfo* worldInfo = readFile.getWorldInfo();


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

	fwrite("P6 ", 1, 3, file);
	fwrite("500", 1, 4, file); // width
	fwrite("500", 1, 4, file); // height
	fwrite("255", 1, 4, file);

	Color bgColor = worldInfo->getBgColor();
	cout << "BgColor in main: " << bgColor.r << " " << bgColor.g << " " << bgColor.b << endl;

	unsigned char pixels[H][W][3];


	cout << H << " " << W << endl;

	for(int h = 0; h < H; h++) {
		for(int w = 0; w < W; w++) {
			pixels[h][w][0] = bgColor.r;
			pixels[h][w][1] = bgColor.g;
			pixels[h][w][2] = bgColor.b;
		}
	}
	fwrite(pixels, 1, H*W*3, file);

	fclose(file);

	vector<Vector> vecs;
	{
		Vector vec1(1, 2, 3);
		Vector vec2;
		vec2 = vec1.scalar(vec1, 4);
		vecs.push_back(vec1);
		vecs.push_back(vec2);
	}

	cout << "testing polies" << endl;
	vector<Polygun* > polys = worldInfo->getPolygun();
	for(unsigned int i = 0; i < polys.size(); i++) {
		cout << "Polygun " << i + 1 << endl;
		for(unsigned int j = 0; j < polys[i]->polyEdges.size(); j++) {
			cout << polys[i]->polyEdges[j] << " ";
		}
	}
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
