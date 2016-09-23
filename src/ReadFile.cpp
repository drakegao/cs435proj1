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

    /* for ployguns storage */
    vector<Vector> Vectors;
    vector<Polygun*> polys;
	this->readFromFile.open(fileName.c_str());
	string readLines;
	if(readFromFile.is_open() && !readFromFile.eof()) {
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

				} else if(readLine == "l") {
					double x, y, z;
					iss >> x >> y >> z;
					Vector lightPos(x, y, z);
					Light light(lightPos);
					this->worldInfo->light = light;

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

				} else if(readLine == "pp") {
					type = "pp";
					iss >> polySize;

				} else if(readLine == "f") {
					double r, g, b, kd, ks, shine, T, index;
					iss >> r >> g >> b >> kd >> ks >> shine >> T >> index;
					// store fillColor here
					FillColor fillColor(r, g, b, kd, ks, shine, T, index);
					this->worldInfo->setFillColor(fillColor);

				} else if(readLine == "s") {
					cout << "sphere" << endl;

				} else {

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
					} else if(type == "p" && polySize != 0) {
						vector<double> value;

						/* in this if condition, the readLine will be the first x value of a polygun */
						istringstream iss2(readLine);
						double x;
						iss2 >> x;
						value.push_back(x);
						double i;
						while(iss >> i) {
							value.push_back(i);
						}

						/* get the first vector position value */
						Vector vec(value[0], value[1], value[2]);

						/* store the polygun's vector value */
						Vectors.push_back(vec);
						polySize--;

						/* when the first polygun info is finished reading */
						if(polySize == 0) {

							/* create new ploygun */
							unsigned int size = Vectors.size();
							if(size == 3) {
								Polygun* poly = new Polygun();
								for(unsigned int j = 0; j < size; j++) {
									/* Vectors[..] will be copied to Polygun's vector<Vectors> */
									poly->polyEdges.push_back(Vectors[j]);
									poly->fillColor = this->worldInfo->getFillColor();
								}

								/* store the first polygun to polygun vector */
								polys.push_back(poly);
							} else if(size > 3) {

								/* fan out polyguns into triangles */
								for(unsigned int k = 1; k < size - 1; k++) {
									Polygun* poly = new Polygun();
									poly->polyEdges.push_back(Vectors[0]);
									poly->polyEdges.push_back(Vectors[k]);
									poly->polyEdges.push_back(Vectors[k + 1]);
									poly->fillColor = this->worldInfo->getFillColor();
									polys.push_back(poly);
								}
							}

							Vectors.clear();
						}
					} else if(type == "pp" && polySize != 0) {
						double x, y, z, xN, yN, zN;

						vector<double> value;

						/* in this if condition, the readLine will be the first x value of a polygun */
						istringstream iss2(readLine);

						iss2 >> x;
						iss >> y >> z >> xN >> yN >> zN;
						value.push_back(x);


						/* get the first vector position value */
						Vector vec(x, y, z, xN, yN, zN);

						/* store the polygun's vector value */
						Vectors.push_back(vec);
						polySize--;

						/* when the first polygun info is finished reading */
						if(polySize == 0) {

							/* create new ploygun */
							unsigned int size = Vectors.size();
							if(size == 3) {
								Polygun* poly = new Polygun();
								for(unsigned int j = 0; j < size; j++) {
									/* Vectors[..] will be copied to Polygun's vector<Vectors> */
									poly->polyEdges.push_back(Vectors[j]);
									poly->fillColor = this->worldInfo->getFillColor();
								}

								/* store the first polygun to polygun vector */
								polys.push_back(poly);
							} else if(size > 3) {

								/* fan out polyguns into triangles */
								for(unsigned int k = 1; k < size - 1; k++) {
									Polygun* poly = new Polygun();
									poly->polyEdges.push_back(Vectors[0]);
									poly->polyEdges.push_back(Vectors[k]);
									poly->polyEdges.push_back(Vectors[k + 1]);
									poly->fillColor = this->worldInfo->getFillColor();
									polys.push_back(poly);
								}
							}

							Vectors.clear();
						}
					}
				}
			}
		}
	}
	this->worldInfo->setView(v);
	this->worldInfo->setPolygun(polys); // get all polyguns
}
