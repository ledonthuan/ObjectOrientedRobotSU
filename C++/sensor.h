//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
/*
 sensor.h
 Don-Thuan Le
 CPSC 3200
 Date: 5/28/2020
 
 Interface Invariants:
 - constructor must be initialized with enum Direction
 - Battery discharge rate is randomly determined
 - Rotating sensor takes in a string of left, right or straight
 - state becomes false if battery level falls below 100
 - comparing sensors will compare the battery levels
 
 Class Invariants:
 - Battery state will become false once the battery level drops below 100
 - isValid will only run if the battery level is above 90% to guarantee the sensor is correctly sensing
 - charging a sensor takes 2 seconds
 - arithmetic operators are not implemented beacuse it does not make sense to add sensors together
 - comparative operators exist to compare the battery level on the sensors
 - only way to reset battery level is to charge sensors back up
 
 */

#ifndef sensor_h
#define sensor_h

#include "grid.h"
#include "Direction.h"

#include <stdio.h>

class sensor {
protected:
	bool state;
	unsigned int batteryLevel;
	unsigned int dischargeRate;
	Direction sensorDirection;

public:
	sensor();
	sensor(Direction senDirection);
	sensor(const sensor& obj);
	sensor& operator=(const sensor&& obj);
    bool operator==(const sensor& obj);
    bool operator!=(const sensor& obj);
    bool operator<(const sensor& obj);
    bool operator>(const sensor& obj);
    bool operator<=(const sensor& obj);
    bool operator>=(const sensor& obj);
	~sensor();

	// PreConditions: state is on
	// PostConditions: discharges the battery
	bool isValid(grid& mainGrid, int posR, int posC);
    // PreConditions:
    // PostConditions: state returns to true, battery level to 1000
	void charge();
    // PreConditions: only right, left or straight
    // PostConditions: changes the direction of the sensor
	Direction sensorRotate(std::string turn);
    unsigned int getBatteryLevel();
    unsigned int getDischargeRate();
};

#endif /* sensor_h */

/*
 Implementation Invariants:
 - battery level and discharge rate are unsigned integers
 - arithmetic operators are not implemented beacuse it does not make sense to add sensors together
 - comparative operators exist to compare the battery level on the sensors
 */
