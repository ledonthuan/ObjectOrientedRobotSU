#include "rotatingRobot.h"
#include <iostream>
#include <string>

rotatingRobot::rotatingRobot(grid& main) : robot(main) {
	RobotDirection = Up;

    list<sensor*>* sensorsLeft = new list<sensor*>();
    list<sensor*>* sensorsRight = new list<sensor*>();
	makeSensors(sensorsLeft, Left);
	makeSensors(sensorsRight, Right);

    sensors->insert({ Left, sensorsLeft });
    sensors->insert({Right, sensorsRight});
}

rotatingRobot::rotatingRobot(const rotatingRobot& obj) : robot(obj){
    RobotDirection = obj.RobotDirection;
    Next = obj.Next;
}

rotatingRobot& rotatingRobot::operator=(const rotatingRobot& obj){
    if (this != &obj){
        RobotDirection = obj.RobotDirection;
        Next = obj.Next;
        this->robot::operator=(obj);
    }
    return *this;
}

rotatingRobot::~rotatingRobot(){
}

bool rotatingRobot::isValid() {
    list<sensor*>* currRobotDirectionSensors = (*sensors)[RobotDirection];
    if(!allSensorBatteryCheck(currRobotDirectionSensors))
        chargeSensors();
    for (sensor* sensor : *currRobotDirectionSensors){
        if (sensor->isValid(mainGrid, posR, posC))
        {
            Next = nextDirection(RobotDirection);
            return true;
        }
    }

    for (std::pair<Direction, list<sensor*>*> element : *sensors) {
        list<sensor*>* currSensors = element.second;
        if(!allSensorBatteryCheck(currSensors))
            chargeSensors();
        for(sensor* temp: *currSensors){
            if (element.first != oppositeDirection(RobotDirection) && temp->isValid(mainGrid, posR, posC)){
                Next = nextDirection(element.first);
                return true;
            }
        }
    }
    return false;
}

std::string rotatingRobot::nextDirection(Direction directionTo){
    switch (RobotDirection){
        case Up:
            if (directionTo == Left)
                return "left";
            else if (directionTo == Right)
                return "right";
            break;
        case Down:
            if (directionTo == Left)
                return "right";
            else if (directionTo == Right)
                return "left";
            break;
        case Left:
            if (directionTo == Up)
                return "right";
            else if (directionTo == Down)
                return "left";
            break;
        case Right:
            if (directionTo == Up)
                return "left";
            else if (directionTo == Down)
                return "right";
            break;
    }
    if (RobotDirection == directionTo)
        return "straight";
    return NULL;
}

bool rotatingRobot::moveOne(){
    if(isValid()){
        if(Next == "left")
            rotate(Next);
        else if(Next == "right")
            rotate(Next);
        else if(Next == "straight"){
            (*actuators)[RobotDirection]->moveForward(*this);
            CountMoves++;
        }
        return true;
    }
    return false;
}

void rotatingRobot::rotate(std::string turn){
    switch (RobotDirection)
    {
        case Up:
            if (turn == "right")
            {
                RobotDirection = Right;
            }
            else if (turn == "left")
            {
                RobotDirection = Left;
            }
            break;
        case Right:
            if (turn == "right")
            {
                RobotDirection = Down;
            }
            else if (turn == "left")
            {
                RobotDirection = Up;
            }
            break;
        case Down:
            if (turn == "right")
            {
                RobotDirection = Left;
            }
            else if (turn == "left")
            {
                RobotDirection = Right;
            }
            break;
        case Left:
            if (turn == "right")
            {
                RobotDirection = Up;
            }
            else if (turn == "left")
            {
                RobotDirection = Down;
            }
            break;
    }
    
    map<Direction, list<sensor*>*>* SensorsTemp = new map<Direction, list<sensor*>*>();
    
    for (std::pair<Direction, list<sensor*>*> element : *sensors) {
        Direction newDirection;
        for(sensor* temp: *(element.second)){
            newDirection = temp->sensorRotate(turn);
        }
        (*SensorsTemp)[newDirection] = element.second;
    }
    delete sensors;
    sensors = SensorsTemp;

    map<Direction, actuator*>* ActuatorsTemp = new map<Direction, actuator*>();
    
    for (std::pair<Direction, actuator*> element : *actuators) {
        Direction newDirection = element.second->actuatorRotate(turn);
        (*ActuatorsTemp)[newDirection] = element.second;
    }
    delete actuators;
    actuators = ActuatorsTemp;
}

Direction rotatingRobot::getRobotDirection(){
    return RobotDirection;
}

Direction rotatingRobot::oppositeDirection(Direction currDirection)
{
    switch (currDirection)
    {
        case Up:
            return Down;
        case Down:
            return Up;
        case Left:
            return Right;
        case Right:
            return Left;
        default:
            break;
    }
    return None;
}




