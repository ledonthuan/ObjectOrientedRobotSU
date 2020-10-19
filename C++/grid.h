//  Created by Don-Thuan Le on 4/24/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
/*
grid.h
Don-Thuan Le
CPSC 3200
Date: 5/28/2020

Interface Invariants:


Class Invariants:

*/

#ifndef grid_h
#define grid_h

#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

class grid{
    std::vector<int*> array;
//	static grid _instance;
    
public:
    grid(std::string filepath);
//	static grid Instance(std::string filepath);
    ~grid();
    
    // PreConditions: pass in position of the robot
    // PostConditions: verifies if next position can be moved to
    bool isPath(int row, int col);
};

#endif /* grid_hpp */

