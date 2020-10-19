//  Created by Don-Thuan Le on 5/29/20.
//  Copyright © 2020 Don-Thuan Le. All rights reserved.
//
/*
tranRobot.h
Don-Thuan Le
CPSC 3200
Date: 5/28/2020

Interface Invariants:
 - tranRobot has inherited class robot
 - this class has an added data member: Next
 - move will go through the whole maze, once reaching the end the robot will go backwards through the maze
 - can call count moves1


Class Invariants:
 - Next is a Direction enum that tells us what direction we will be heading in
 - has 4 actuators and 20 sensors
 - forward, back, left, and right just move the respective actuators and therefore moving the robot
 -  supports == and != to compare the move count between two robots

*/

#ifndef tranRobot_h
#define tranRobot_h

#include "actuator.h"
#include "Direction.h"

#include <stdio.h>

class tranRobot: public robot{
protected:
    Direction Next;
    
public:
    tranRobot(grid&);
    tranRobot(const tranRobot& obj);
    virtual tranRobot& operator=(const tranRobot& obj);
    virtual ~tranRobot();
    virtual bool isValid();
    // PreConditions:
    // PostConditions: moves robot one grid point
    virtual bool moveOne();
    virtual Direction oppositeDirection(Direction);
    // PreConditions:
    // PostConditions: moves respective actuator
    void forward();
    // PreConditions:
    // PostConditions: moves respective actuator
    void back();
    // PreConditions:
    // PostConditions: moves respective actuator
    void left();
    // PreConditions:
    // PostConditions: moves respective actuator
    void right();
};

#endif /* tranRobot_hpp */

/*
 Implementation Invariant:
 - once at the end, the robot will proceed to go backwards
 - when going through the amaze, the robot ignores the backwards direction as to not go the opposite direction of where we want
 - unlike rotational robot, tranRobot does not change direction
 - 4 actuators allows it to just move each actuator respectively
 */
