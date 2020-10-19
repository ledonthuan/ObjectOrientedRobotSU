/*
rotatingRobot.h
Don-Thuan Le
CPSC 3200
Date: 5/28/2020

Interface Invariants:
- Has inherited robot class as a base class with added data members: Next and robot direction
 - robot now has sensors in 3 directions
 - you can rotate the robot so that the sensors are pointing
 - robot does not charge unless it has stopped moving

Class Invariants:
 - Next is a string and not an enum so it doesn't cross with the direction enum
 - Robot direction tells us which way the robot is facing
 - move is inherited from the base class
 - has 1 actuator 15 sensors
*/
#ifndef rotatingRobot_h
#define rotatingRobot_h


#include "Direction.h"
#include "actuator.h"

using namespace std;

class rotatingRobot: public robot{
protected:
	std::string Next;
	Direction RobotDirection;

public:
	rotatingRobot(grid& main);
    
    rotatingRobot(const rotatingRobot& obj);
    virtual rotatingRobot& operator=(const rotatingRobot& obj);
    virtual ~rotatingRobot();
    virtual bool isValid();
	virtual std::string nextDirection(Direction directionTo);
    // PreConditions:
    // PostConditions: moves robot one grid point
	virtual bool moveOne();
    // PreConditions:
    // PostConditions: changes the direction of the robot
	virtual void rotate(std::string turn);
	virtual Direction getRobotDirection();
    Direction oppositeDirection(Direction currDirection);
};

#endif /* rotatingRobot_h */

/*
 Implementation Invariants:
 - we avoid checking the sensor for the opposite direction of the way we are going because we do not want to move backwards
 - oppositeDirections helps with avoiding checking the sensors that are opposite of the way we are heading so that we do not head backwards
 - count moves is incremented in move one
 - a for each loop is used to rotate the sensors with a temp sensor holder so that we can replace the sensors in the map with different keys
 - the above goes for actuators too
 - move is called which calls moveOne in a loop. moveOne calls isValid and rotate or actuators moveForward respectively
 */
