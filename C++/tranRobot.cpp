//
//  tranRobot.cpp
//  P4
//
//  Created by Don-Thuan Le on 5/29/20.
//  Copyright © 2020 Don-Thuan Le. All rights reserved.
//

#include "tranRobot.h"
#include <iostream>


tranRobot::tranRobot(grid& main) : robot(main){
    Next = Up;
    
    list<sensor*>* sensorsLeft = new list<sensor*>();
    list<sensor*>* sensorsRight = new list<sensor*>();
    list<sensor*>* sensorsDown = new list<sensor*>();
    makeSensors(sensorsLeft, Left);
    makeSensors(sensorsRight, Right);
    makeSensors(sensorsDown, Down);

    sensors->insert({ Left, sensorsLeft });
    sensors->insert({Right, sensorsRight});
    sensors->insert({Down, sensorsDown});
    actuators->insert({ Left, new actuator(Left) });
    actuators->insert({Right, new actuator(Right)});
    actuators->insert({Down, new actuator(Down)});
}

tranRobot::tranRobot(const tranRobot& obj) : robot(obj){
    Next = obj.Next;
}

tranRobot& tranRobot::operator=(const tranRobot& obj){
    if (this != &obj){
        Next = obj.Next;
        //*((robot*)this)=obj;
        this->robot::operator=(obj);
    }
    return *this;
}

tranRobot::~tranRobot(){}

bool tranRobot::isValid(){
    list<sensor*>* currRobotDirectionSensors = (*sensors)[Next];
    if(!allSensorBatteryCheck(currRobotDirectionSensors))
        chargeSensors();
    for (sensor* sensor : *((*sensors)[Next])){
        if (sensor->isValid(mainGrid, posR, posC))
        {
            return true;
        }
    }
    
    for (std::pair<Direction, list<sensor*>*> element : *sensors) {
        list<sensor*>* currSensors = element.second;
        if(!allSensorBatteryCheck(currSensors))
            chargeSensors();
        for(sensor* temp: *(element.second)){
            if (element.first != oppositeDirection(Next) && temp->isValid(mainGrid, posR, posC)){
                Next = element.first;
                return true;
            }
        }
    }
    return false;
}

bool tranRobot::moveOne(){
    //chargesensors
    if(isValid()){
        switch(Next){
            case Up:
                forward();
                break;
            case Down:
                back();
                break;
            case Left:
                left();
                break;
            case Right:
                right();
                break;
        }
        CountMoves++;
        return true;
    }
    return false;
}

Direction tranRobot::oppositeDirection(Direction currDirection){
    switch(currDirection){
        case Up:
            return Down;
        case Down:
            return Up;
        case Left:
            return Right;
        case Right:
            return Left;
    }
    return None;
}

void tranRobot::forward(){
    (*actuators)[Up]->moveForward(*this);
}

void tranRobot::back(){
    (*actuators)[Down]->moveForward(*this);
}

void tranRobot::left(){
    (*actuators)[Left]->moveForward(*this);
}

void tranRobot::right(){
    (*actuators)[Right]->moveForward(*this);
}
