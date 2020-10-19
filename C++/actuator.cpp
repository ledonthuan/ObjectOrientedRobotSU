//
//  actuator.cpp
//  P2
//
//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
// Implementation Invariant:
// This actuator class has two main functions, moveForward() and isPoweredup().
// These two functions are dependent on paramenters passed in from the robot class
// such as the position of the robot on the grid and the on/off state of the robot.
//
//
//
//
#include "actuator.h"
#include "robot.h"
#include <algorithm>

actuator::actuator() {
	state = true;
	actuatorDirection = Up;
}

actuator::actuator(Direction direction) {
	this->state = true;
	this->actuatorDirection = direction;
}

actuator::actuator(const actuator &obj) {
	state = obj.state;
	actuatorDirection = obj.actuatorDirection;
}

actuator& actuator::operator=(const actuator&& obj) {
	if (this != &obj) {
		state = obj.state;
		actuatorDirection = obj.actuatorDirection;
	}

	return *this;
}

bool actuator::operator==(const actuator& obj){
    if (this != &obj)
        return false;
    return true;
}

bool actuator::operator!=(const actuator& obj){
    if (this == &obj)
        return false;
    return true;
}

actuator::~actuator() {}

void actuator::moveForward(robot& R1) {
	if (R1.isPoweredUp())
	{
		switch (actuatorDirection)
		{
		case Up:
			if (R1.getPosR() != 0)
				R1.setPosR(R1.getPosR() - 1);
			break;
		case Down:
			if (R1.getPosR() != 10)
				R1.setPosR(R1.getPosR() + 1);
			break;
		case Left:
			if (R1.getPosC() != 0)
				R1.setPosC(R1.getPosC() - 1);
			break;
		case Right:
			if (R1.getPosC() != 10)
				R1.setPosC(R1.getPosC() + 1);
			break;
		}
	}
}

Direction actuator::getDirection() {
	return actuatorDirection;
}

Direction actuator::actuatorRotate(std::string turn) {
	std::for_each(turn.begin(), turn.end(), [](char & c) {
		c = ::tolower(c);
	});

	switch (actuatorDirection)
	{
	case Up:
		if (turn == "right")
		{
			actuatorDirection = Right;
		}
		else if (turn == "left")
		{
			actuatorDirection = Left;
		}
		break;
	case Right:
		if (turn == "right")
		{
			actuatorDirection = Down;
		}
		else if (turn == "left")
		{
			actuatorDirection = Up;
		}
		break;
	case Down:
		if (turn == "right")
		{
			actuatorDirection = Left;
		}
		else if (turn == "left")
		{
			actuatorDirection = Right;
		}
		break;
	case Left:
		if (turn == "right")
		{
			actuatorDirection = Up;
		}
		else if (turn == "left")
		{
			actuatorDirection = Down;
		}
		break;
	}
	return actuatorDirection;
}




