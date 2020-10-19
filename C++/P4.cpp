//  Created by Don-Thuan Le on 4/19/20.
//  Copyright � 2020 Don-Thuan Le. All rights reserved.
//
/*
 P4.cpp
 Don-Thuan Le
 CPSC 3200
 Date: 5/29/2020
 
 This driver is a comprehensive test of the class robot, rotatingRobot, and tranRobot. The goal over this driver to is
 show dependency injection and test all overloaded operators. Each test function tests an overloaded operator
 for all three classes. The functions will output 3 scenarios with their expected boolean value and the actual boolean
 value varifying the validity and the implementation of the overloaded operator. The last test is a test of the
 heterogeneous collection held in a vector and put into a loop and called move(). There are a total of nine test
 functions: Copy Constructor, =, <, >, <=, >=, ==, !=, and a heterogenous collection.
 
 */
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "rotatingRobot.h"
#include "robot.h"
#include "tranRobot.h"
#include "grid.h"

using namespace std;

void testCopyConstructor(grid& mainGrid){
    cout << "Testing Copy Constructor" << endl;
    shared_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    robot* r2 = new robot(*r1);
    cout << "r3 countMoves: " << r1->getCountMoves() << endl;
    cout << "r4 countMoves: " << r2->getCountMoves() << endl;
    
    shared_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    rotatingRobot* r4 = new rotatingRobot(*r3);
    cout << "r1 countMoves: " << r3->getCountMoves() << endl;
    cout << "r2 countMoves: " << r4->getCountMoves() << endl;
    
    shared_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    tranRobot* r6 = new tranRobot(*r5);
    cout << "r5 countMoves: " << r5->getCountMoves() << endl;
    cout << "r6 countMoves: " << r6->getCountMoves() << endl;
}

void testAssignmentOperator(grid& mainGrid){
    cout << "Testing Overloaded Assignment Operator" << endl;
    shared_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    shared_ptr<robot> r2 (r1);
    cout << "r3 countMoves: " << r1->getCountMoves() << endl;
    cout << "r4 countMoves: " << r2->getCountMoves() << endl;
    
    shared_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    shared_ptr<rotatingRobot> r4 (r3);
    cout << "r1 countMoves: " << r3->getCountMoves() << endl;
    cout << "r2 countMoves: " << r4->getCountMoves() << endl;
    
    shared_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    shared_ptr<tranRobot> r6 (r5);
    cout << "r5 countMoves: " << r5->getCountMoves() << endl;
    cout << "r6 countMoves: " << r6->getCountMoves() << endl;
}

void testLessThanOperator(grid& mainGrid){
    cout << "Testing < Operator" << endl;
    unique_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    unique_ptr<robot> r2 (new robot(mainGrid));
    cout << "r2 < r1, expected: " << (r2->getCountMoves() < r1->getCountMoves()) << ", actual: " << (*r2<*r1) << endl;
    
    unique_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    unique_ptr<rotatingRobot> r4 (new rotatingRobot(mainGrid));
    cout << "r4 < r3, expected: " << (r4->getCountMoves() < r3->getCountMoves()) << ", actual: " << (*r4<*r3) << endl;
    
    unique_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    unique_ptr<tranRobot> r6 (new tranRobot(mainGrid));
    cout << "r6 < r5, expected: " << (r6->getCountMoves() < r5->getCountMoves()) << ", actual: " << (*r6<*r5) << endl;
}

void testGreaterThanOperator(grid& mainGrid){
    cout << "Testing > Operator" << endl;
    unique_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    unique_ptr<robot> r2 (new robot(mainGrid));
    cout << "r1 > r2, expected: " << (r1->getCountMoves() > r2->getCountMoves()) << ", actual: " << (*r1>*r2) << endl;
    
    unique_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    unique_ptr<rotatingRobot> r4 (new rotatingRobot(mainGrid));
    cout << "r3 > r4, expected: " << (r3->getCountMoves() > r4->getCountMoves()) << ", actual: " << (*r3>*r4) << endl;
    
    unique_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    unique_ptr<tranRobot> r6 (new tranRobot(mainGrid));
    cout << "r5 > r6, expected: " << (r5->getCountMoves() > r6->getCountMoves()) << ", actual: " << (*r5>*r6) << endl;
}

void testGreaterThanOrEqualToOperator(grid& mainGrid){
    cout << "Testing >= Operator" << endl;
    unique_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    unique_ptr<robot> r2 (new robot(mainGrid));
    r2->move();
    cout << "r1 >= r2, expected: " << (r1->getCountMoves() >= r2->getCountMoves()) << ", actual: " << (*r1>=*r2) << endl;
    
    unique_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    unique_ptr<rotatingRobot> r4 (new rotatingRobot(mainGrid));
    cout << "r3 >= r4, expected: " << (r3->getCountMoves() >= r4->getCountMoves()) << ", actual: " << (*r3>=*r4) << endl;
    
    unique_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    unique_ptr<tranRobot> r6 (new tranRobot(mainGrid));
    r6->move();
    cout << "r5 >= r6, expected: " << (r5->getCountMoves() >= r6->getCountMoves()) << ", actual: " << (*r5>=*r6) << endl;
}

void testLessThanOrEqualToOperator(grid& mainGrid){
    cout << "Testing <= Operator" << endl;
    unique_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    unique_ptr<robot> r2 (new robot(mainGrid));
    r2->move();
    cout << "r1 <= r2, expected: " << (r1->getCountMoves() <= r2->getCountMoves()) << ", actual: " << (*r1<=*r2) << endl;
    
    unique_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    unique_ptr<rotatingRobot> r4 (new rotatingRobot(mainGrid));
    cout << "r3 <= r4, expected: " << (r3->getCountMoves() <= r4->getCountMoves()) << ", actual: " << (*r3<=*r4) << endl;
    
    unique_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    unique_ptr<tranRobot> r6 (new tranRobot(mainGrid));
    r6->move();
    cout << "r5 <= r6, expected: " << (r5->getCountMoves() <= r6->getCountMoves()) << ", actual: " << (*r5<=*r6) << endl;
}

void testEqualEqualOperator(grid& mainGrid){
    cout << "Testing == Operator" << endl;
    unique_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    unique_ptr<robot> r2 (new robot(mainGrid));
    r2->move();
    cout << "r1 == r2, expected: 0, actual: " << (*r1==*r2) << endl;
    
    unique_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    unique_ptr<rotatingRobot> r4 (new rotatingRobot(mainGrid));
    cout << "r3 == r4, expected: 0, actual: " << (*r3==*r4) << endl;
    
    unique_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    cout << "r5 == r5, expected: 1, actual: " << (*r5==*r5) << endl;
}

void testNotEqualOperator(grid& mainGrid){
    cout << "Testing != Operator" << endl;
    unique_ptr<robot> r1 (new robot(mainGrid));
    r1->move();
    unique_ptr<robot> r2 (new robot(mainGrid));
    r2->move();
    cout << "r1 != r2, expected: 1, actual: " << (*r1!=*r2) << endl;
    
    unique_ptr<rotatingRobot> r3 (new rotatingRobot(mainGrid));
    r3->move();
    unique_ptr<rotatingRobot> r4 (new rotatingRobot(mainGrid));
    cout << "r3 != r4, expected: 1, actual: " << (*r3!=*r4) << endl;
    
    unique_ptr<tranRobot> r5 (new tranRobot(mainGrid));
    r5->move();
    cout << "r5 != r5, expected: 0, actual: " << (*r5!=*r5) << endl;
}

void testHeterogeneous(grid& mainGrid){
    vector<robot*> heterogeneous;
    
    heterogeneous.push_back(new robot(mainGrid));
    heterogeneous.push_back(new rotatingRobot(mainGrid));
    heterogeneous.push_back(new tranRobot(mainGrid));
    
    for (robot* oneRobot: heterogeneous){
        oneRobot->move();
        cout << typeid(*oneRobot).name() << endl;
        cout << "countMoves: " << oneRobot->getCountMoves() << endl;
    }
    
}

int main(int argc, const char * argv[]) {
	grid mainGrid = grid(argv[1]);
    
    testCopyConstructor(mainGrid);
    testAssignmentOperator(mainGrid);
    testLessThanOperator(mainGrid);
    testGreaterThanOperator(mainGrid);
    testGreaterThanOrEqualToOperator(mainGrid);
    testLessThanOrEqualToOperator(mainGrid);
    testEqualEqualOperator(mainGrid);
    testNotEqualOperator(mainGrid);
    testHeterogeneous(mainGrid);
}

