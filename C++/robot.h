//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
/*
robot.h
Don-Thuan Le
CPSC 3200
Date: 5/28/2020

Interface Invariants:
 - calling move is a while loop of moveOne which will navigate the whil maze
- state of the robot is assumed to be always true
 - interface supports the operators: =, ==, and !=
 - robot is intialized with a reference to a grid for the robot to move on
 - you can get the number of moves the robot has made
 - calling charge sensors will charge all the sensors
 - robot default starting position is 5,5
 - supports operators: = , ==, !=
 - does not support arithmetic operators

Class Invariants:
 - position values are integers so that you can detect when you are reaching less than 0
 - grid is a reference from a class grid - so that every robot does not have a copy of the same exact grid but can share to save resources
 - does not support arithmetic operators, cannot add or subtract robots from each other
 - a map is used to the sensors and actuators
 - has 5 sensors and one actuator
*/
#ifndef robot_h
#define robot_h

#include "sensor.h"
#include "grid.h"
#include "Direction.h"

#include <memory>
#include <stdio.h>
#include <map>
#include <list>

using namespace std;
class actuator;
class robot {
protected: 
	bool state;
	map<Direction, list<sensor*>*>* sensors;
    map<Direction, actuator*>* actuators;
	int posC;
	int posR;

	grid& mainGrid;

	void makeSensors(list<sensor*>* listSensors, Direction SensorDirection);
    
    int CountMoves = 0;

public:
	robot(grid& main);
	robot(const robot& obj);
    virtual robot& operator=(const robot& obj);
    bool operator==(const robot& obj);
    bool operator!=(const robot& obj);
    bool operator<(const robot& obj);
    bool operator>(const robot& obj);
    bool operator<=(const robot& obj);
    bool operator>=(const robot& obj);
    
	virtual ~robot();

	const unsigned int DEFAULT_POSITION = 5;

    // PreConditions:
    // PostConditions: discharges the battery
	virtual bool isValid();
	virtual void move();
	virtual bool moveOne();
	virtual bool isPoweredUp();

    // PreConditions:
    // PostConditions: charges all sensors
	virtual void chargeSensors();

	virtual int getPosR();
	virtual int getPosC();
    // PreConditions:
    // PostConditions: allows actuator to change robot position
	virtual void setPosR(int pos);
    // PreConditions:
    // PostConditions: allows actuator change robot position
	virtual void setPosC(int pos);
    virtual int getCountMoves();
    virtual bool batteryCheck(sensor*);
    virtual bool allSensorBatteryCheck(list<sensor*>*);
};

#endif /* robot_hpp */

/*
 Implementation Invariants:
 - sensors and actuators are held in individual maps
 - sensors is overall a triple pointer: sensors for each direction is held in a list of pointers to each individual sensor
 - actuators is a double pointer
 - movement of the robots position takes place in the actuator class
 - grid is a reference to save resources - has its own class
 - assignment operator utilizes move semantics
 */
