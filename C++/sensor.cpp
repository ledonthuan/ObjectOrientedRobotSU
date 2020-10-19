//
//  sensor.cpp
//  P2
//
//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
// Implementation Invariant:
// the sensor takes in the grid and position of the robot in isValid()
// to verify if the next position is available to move to in the direction
// you want to move. 
//
#include "sensor.h"

#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <string>
#include <algorithm>
#include <iostream>

sensor::sensor() {
	srand((unsigned)time(0));
	state = true;
	batteryLevel = 1000;
	dischargeRate = (rand() % 1000) + 1;
	sensorDirection = Up;
}

sensor::sensor(Direction senDirection) {
	srand((unsigned)time(0));
	state = true;
	batteryLevel = 1000;
    dischargeRate = (rand() % 1000) + 1;
	sensorDirection = senDirection;
}

sensor::sensor(const sensor& obj) {
	state = obj.state;
	batteryLevel = obj.batteryLevel;
	dischargeRate = obj.dischargeRate;
	sensorDirection = obj.sensorDirection;
}

sensor& sensor::operator=(const sensor&& obj) {
	if (this != &obj) {
		state = obj.state;
		batteryLevel = obj.batteryLevel;
		dischargeRate = obj.dischargeRate;
		sensorDirection = obj.sensorDirection;
	}
	return *this;
}

bool sensor::operator==(const sensor& obj){
    return (batteryLevel == obj.batteryLevel);
}

bool sensor::operator!=(const sensor& obj){
    return (batteryLevel != obj.batteryLevel);
}

bool sensor::operator<(const sensor& obj){
    return (batteryLevel < obj.batteryLevel);
}

bool sensor::operator>(const sensor& obj){
    return (batteryLevel > obj.batteryLevel);
}

bool sensor::operator<=(const sensor& obj){
    return (batteryLevel <= obj.batteryLevel);
}

bool sensor::operator>=(const sensor& obj){
    return (batteryLevel >= obj.batteryLevel);
}

sensor::~sensor() {}

bool sensor::isValid(grid& mainGrid, int posR, int posC) {
	if (state) {
		if (batteryLevel < dischargeRate)
			return false;
		else if (batteryLevel < 900)
			return false;
		else {
			batteryLevel -= dischargeRate;
            if (batteryLevel < 100)
                state = false;
			switch (sensorDirection)
			{
                case Up:
                    return mainGrid.isPath(posR - 1, posC);
                case Down:
                    return mainGrid.isPath(posR + 1, posC);
                case Left:
                    return mainGrid.isPath(posR, posC - 1);
                case Right:
                    return mainGrid.isPath(posR, posC + 1);
                case None:
                    return false;
			}
		}
	}
	return false;
}

void sensor::charge() {
	state = true;
	batteryLevel = 1000;
	sleep(.1);
}

Direction sensor::sensorRotate(std::string turn) {
    std::transform(turn.begin(), turn.end(), turn.begin(), ::tolower);
    
	switch (sensorDirection)
	{
        case Up:
            if (turn == "right")
            {
                sensorDirection = Right;
            }
            else if (turn == "left")
            {
                sensorDirection = Left;
            }
            break;
        case Right:
            if (turn == "right")
            {
                sensorDirection = Down;
            }
            else if (turn == "left")
            {
                sensorDirection = Up;
            }
            break;
        case Down:
            if (turn == "right")
            {
                sensorDirection = Left;
            }
            else if (turn == "left")
            {
                sensorDirection = Right;
            }
            break;
        case Left:
            if (turn == "right")
            {
                sensorDirection = Up;
            }
            else if (turn == "left")
            {
                sensorDirection = Down;
            }
            break;
	}
	return sensorDirection;
}

unsigned int sensor::getBatteryLevel(){
    return batteryLevel;
}

unsigned int sensor::getDischargeRate(){
    return dischargeRate;
}
