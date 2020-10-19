//
//  grid.cpp
//  P2
//
//  Created by Don-Thuan Le on 4/24/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
// Implementation Invariants:
// This class reads in the grid file to a vector (STL container) of
// int arrays. isPath() function is used in the sensor class to verify
// that the next move is a vlid move for the robot.
//
//
#include "grid.h"
#include <sstream>
#include <stdlib.h>
#include <fstream>

grid::grid(std::string filepath) {
	std::string buf;

	ifstream file;
	file.open(filepath);

	if (file.is_open()) {
		int currRow = 0;
		while (getline(file, buf, '\n')) {
			std::stringstream ss(buf);
			array.push_back(new int[11]);

			int currCol = 0;
			std::string stringBuf;
			while (getline(ss, stringBuf, ' ')) {
				this->array[currRow][currCol] = std::atoi(stringBuf.c_str());
				currCol++;
			}
			currRow++;
		}
	}
    file.close();
}

//static grid Instance(std::string filepath) {
//	if (_instance == NULL)
//		_instance = new grid(filepath);
//	return _instance;
//}

bool grid::isPath(int row, int col) {
	if (row < 0 || row > 10 || col < 0 || col > 10)
		return false;

	return array[row][col] == 1 ? true : false;
}

grid::~grid() {
	for (int* ptr : array) {
		delete[] ptr;
	}
}
