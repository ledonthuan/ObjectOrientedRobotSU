//
//  robot.cpp
//  P2
//
//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
//
// Interface Invariants:
// The robot will only move forward if the sensor has enough battery. In the driver
// file you may notice that sometimes when running the position will end at 4,5
// instead of 3,5 - this is because the sensor did not have enough battery to run
// a second query.
//
// Implementation Invariants:
// robot is required to load in the grid when initialized so that it can be
// placed on the grid. When powered, the robot also powers the actuator, and the
// sensor is powered by its own battery.
//
//
#include "actuator.h"
#include <iostream>

robot::robot(grid& main): mainGrid(main){
	state = true;
    
    sensors = new map<Direction, list<sensor*>*>;
    actuators = new map<Direction, actuator*>;
    
    list<sensor*>* sensorsUp = new list<sensor*>();
	makeSensors(sensorsUp, Up);
	actuators->insert({ Up, new actuator(Up) });
	sensors->insert({Up, sensorsUp});
    posR = DEFAULT_POSITION;
	posC = DEFAULT_POSITION;
}

robot::robot(const robot& obj) : mainGrid(obj.mainGrid) {
    state = obj.state;
    CountMoves = obj.CountMoves;
    posR = obj.posR;
    posC = obj.posC;
    sensors = new map<Direction, list<sensor*>*>;
    actuators = new map<Direction, actuator*>;
    
    for (std::pair<Direction, list<sensor*>*> element : *obj.sensors){
        sensors->insert({element.first, element.second});
    }
    
    for (std::pair<Direction, actuator*> element : *obj.actuators) {
        actuators->insert({element.first, element.second});
    }
}

robot& robot::operator=(const robot& obj) {
	if (this != &obj) {
        delete sensors;
        delete actuators;
        
        state = obj.state;
        sensors = obj.sensors;
        actuators = obj.actuators;
        posR = obj.posR;
        posC = obj.posC;
        CountMoves = obj.CountMoves;
	}
	return *this;
}

bool robot::operator==(const robot& obj){
    if (this != &obj)
        return false;
    return true;
}

bool robot::operator!=(const robot& obj){
    if (this == &obj)
        return false;
    return true;
}

bool robot::operator<(const robot& obj){
    if (this->CountMoves < obj.CountMoves){
        return true;
    }
    return false;
}
bool robot::operator>(const robot& obj){
    return (CountMoves > obj.CountMoves);
}
bool robot::operator<=(const robot& obj){
    return (CountMoves <= obj.CountMoves);
}
bool robot::operator>=(const robot& obj){
    return (CountMoves >= obj.CountMoves);
}

robot::~robot() {
    for (std::pair<Direction, list<sensor*>*> element : *sensors) {
        for(auto* sensor: *(element.second)){
            delete sensor;
        }
        delete element.second;
    }
    
    for (std::pair<Direction, actuator*> element : *actuators) {
        delete element.second;
    }
    
    delete sensors;
    delete actuators;
}

bool robot::isValid() {
    list<sensor*>* upSensors = (*sensors)[Up];
    if(!allSensorBatteryCheck(upSensors))
        chargeSensors();
    for(sensor* upSensor: *upSensors){
        if(upSensor->isValid(mainGrid, posR, posC))
            return true;
    }
    return false;
}

bool robot::allSensorBatteryCheck(list<sensor*>* listsensor){
    for(sensor* temp: *listsensor){
        if (this->batteryCheck(temp)){
            return true;
        }
    }
    return false;
}

void robot::move() {
	bool temp = true;
	while (temp) {
		temp = moveOne();
	}
}

bool robot::moveOne() {
	if (isValid()) {
		(*actuators)[Up]->moveForward(*this);
        CountMoves++;
		return true;
	}
	return false;
}

bool robot::batteryCheck(sensor* sen){
    unsigned int temp = sen->getBatteryLevel();
    if (temp < sen->getDischargeRate()){
        return false;
    }
    else if (temp < 900){
        return false;
    }
    return true;
}

int robot::getPosC() {
	return posC;
}

int robot::getPosR() {
	return posR;
}

void robot::setPosC(int pos) {
	posC = pos;
}

void robot::setPosR(int pos) {
	posR = pos;
}

bool robot::isPoweredUp() {
	return state;
}

void robot::makeSensors(list<sensor*>* listsensor, Direction SensorDirection) {
	sensor* newSensor;
	for (int i = 0; i < 5; i++) {
		newSensor = new sensor(SensorDirection);
		listsensor->push_back(newSensor);
	}
}

void robot::chargeSensors() {
    for (std::pair<Direction, list<sensor*>*> element : *sensors) {
        for(sensor* temp: *(element.second)){
            temp->charge();
        }
    }
}

int robot::getCountMoves(){
    return CountMoves;
}


