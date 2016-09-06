/*
 * ReadFile.cpp
 *
 *  Created on: Sep 3, 2016
 *      Author: drake
 */

#include "ReadFile.h"
#include <sstream>
#include <vector>
#include <cstring>
#include "Vector.h"

using namespace std;
ReadFile::ReadFile() {
	// TODO Auto-generated constructor stub
	this->worldInfo = new WorldInfo();
}

ReadFile::~ReadFile() {
	// TODO Auto-generated destructor stub
	cout << "read file is gone" << endl;
	if(this->worldInfo != NULL) {
		delete worldInfo;
	}
}

WorldInfo* ReadFile::getWorldInfo() {
	return this->worldInfo;
}
void ReadFile::setWorldInfo(WorldInfo* w) {
	this->worldInfo = w;
}

/**
 * Read files and store infomation to ExportPPM class in readfile;
 */
void ReadFile::readFile(string fileName) {
	// type flag;
	string type = "";

	// store polygun vertsize to read;
	int polySize = 0;

	/* for view point store */
    View* v = new View();
	this->readFromFile.open(fileName.c_str());
	string readLines;
	if(readFromFile.is_open() && !readFromFile.eof()) {
		int pCount = 0;

		/* so far it will recognize 'bvfps' command*/
		while(getline(readFromFile, readLines)) {
			istringstream iss(readLines);
			string readLine;

			// check the first letter or word in the command line from file
			iss >> readLine;
			if(readLine[0] != '#') {
				// parse info here
				if(readLine == "v") {
					type = "v";

				} else if(readLine == "b") {
					type = "b";

					/* for background color */
					double r, g, b;
					iss >> r >> g >> b;
					Color bgColor(r, g, b);

					/* set the bgColor*/
					this->worldInfo->setBgColor(bgColor);

				} else if(readLine == "p") {
					type = "p";
					iss >> polySize;

					/* set poly numbers */

				} else if(readLine == "f") {
					double r, g, b, kd, ks, shine, T;
					iss >> r >> g >> b >> kd >> ks >> shine >> T;
					// store fillColor here

				} else if(readLine == "s") {
					cout << "sphere" << endl;

				} else {

					/*from 1.02285 -3.17715 -2.17451
					at -0.004103 -0.004103 0.216539
					up -0.816497 -0.816497 0.816497
					angle 45
					hither 1
					resolution 512 512*/
					if(readLine == "from") {
						double x, y, z;
						iss >> x >> y >> z;
						Vector from(x, y, z);
						v->setFrom(from);

					} else if(readLine == "at") {
						double x, y, z;
						iss >> x >> y >> z;
						Vector at(x, y, z);
						v->setAt(at);
					} else if(readLine == "up") {
						double x, y, z;
						iss >> x >> y >> z;
						Vector up(x, y, z);
						v->setUp(up);

					} else if(readLine == "angle") {
						int angle;
						iss >> angle;
						v->setAngle(angle);
					} else if(readLine == "hither") {
						int hither;
						iss >> hither;
						v->setHither(hither);
					} else if(readLine == "resolution") {
						int W, H;
						iss >> W >> H;
						v->setWidth(W);
						v->setHeight(H);
					}
				}
			}
		}
	}
	this->worldInfo->setView(v);
}
