//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
/*
actuator.h
Don-Thuan Le
CPSC 3200
Date: 5/28/2020

Interface Invariants:
 - actuator only has one data member: the actuator direction
- actuator state depends on the state of the robot, if robot is on so is the actuator
 - calling move is a while loop of moveOne.
 - if not specified, actuator direction will be Up, but you can pass in a direction to the constructor to specify
 - moving the actuator changes the position of the whole robot

Class Invariants:
 - actuator takes in a string (left, right, straight) so as to not confuse with enum direction
 - robot is passed in by reference

*/


#ifndef actuator_h
#define actuator_h

#include "Direction.h"
#include "robot.h"

#include <stdio.h>
#include <string>

class actuator {
protected:
    bool state;
	Direction actuatorDirection;

public:
	actuator();
	actuator(Direction direction);
	actuator(const actuator &obj);
	actuator& operator= (const actuator&& obj);
    bool operator==(const actuator& obj);
    bool operator!=(const actuator& obj);
	~actuator();

	// PreConditions: the position of the robot on the grid passed in by reference
	// PostConditions: change in the position of the robot
    void moveForward(robot& R1);

	Direction getDirection();
    // PreConditions:
    // PostConditions: changes direction of actuator
    Direction actuatorRotate(std::string turn);
};

#endif /* actuator_hpp */

/*
 Implementation Invariant:
 - arithmetic operators are not supported, you can't add or subtract actuators
 - only == and != comparative operators are supported, there is no way to compare one actuator is more than the other
 - actuator takes state from the robot connected to it
 - robot is passed in by reference to moveForward so that the position of the robot can be changed
 */
