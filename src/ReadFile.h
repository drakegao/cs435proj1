/*
 * ReadFile.h
 *
 *  Created on: Sep 3, 2016
 *      Author: drake
 */

#ifndef READFILE_H_
#define READFILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include "WorldInfo.h"

using namespace std;

class ReadFile {
public:
	ReadFile();
	WorldInfo* getWorldInfo();
	void setWorldInfo(WorldInfo* w);
	void readFile(string fileName);
	virtual ~ReadFile();

private:
	ifstream readFromFile;
	WorldInfo* worldInfo;
};

#endif /* READFILE_H_ */
