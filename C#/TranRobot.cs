/* sensor.cs
* Don-Thuan Le
* CPSC3200
* Date: 5/8/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, 4 sensors are made, 4 actuators are made, the starting position is 
* 5,5, the grid is loaded in from the command line and the robot direction is Up.
* 
* Interface Invariants:
* TransRobot does not rotate and it prioritizes the directions that are not opposite to its current 
* direction. This makes it so that the robot does not accidentally move backwards.
*/


using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class TranRobot : Robot
    {
        private Direction Next;

        public TranRobot(string filePath) : base(filePath)
        {
            Sensors[Direction.Left] = new Sensor(Direction.Left);
            Sensors[Direction.Right] = new Sensor(Direction.Right);
            Sensors[Direction.Down] = new Sensor(Direction.Down);

            Actuators[Direction.Left] = new Actuator(Direction.Left);
            Actuators[Direction.Right] = new Actuator(Direction.Right);
            Actuators[Direction.Down] = new Actuator(Direction.Down);

            Next = Direction.Up;
        }

        public TranRobot(string filePath, int PosR1, int PosC1) : base(filePath)
        {
            PosR = PosR1;
            PosC = PosC1;
            Sensors[Direction.Left] = new Sensor(Direction.Left);
            Sensors[Direction.Right] = new Sensor(Direction.Right);
            Sensors[Direction.Down] = new Sensor(Direction.Down);

            Actuators[Direction.Left] = new Actuator(Direction.Left);
            Actuators[Direction.Right] = new Actuator(Direction.Right);
            Actuators[Direction.Down] = new Actuator(Direction.Down);

            Next = Direction.Up;
        }

        public override bool isValid()
        {
            if (IsPoweredup())
            {
                if (Sensors[Next].IsValid(MainGrid, PosR, PosC))
                {
                    return true;
                }

                foreach (var item in Sensors)
                {
                    if (item.Key != Next && item.Key != OppositeDirection(Next))
                    {
                        if (item.Value.IsValid(MainGrid, PosR, PosC))
                        {
                            Next = item.Key;
                            return true;
                        }
                    }
                }
            }
            // Add check backwards if want robot to go back through the maze
            return false;
        }

        public override void move()
        {
            while (moveOne()) ;
        }

        public override bool moveOne()
        {
            ChargeSensors();
            if (isValid())
            {
                switch (Next)
                {
                    case Direction.Up:
                        Forward();
                        break;
                    case Direction.Down:
                        Back();
                        break;
                    case Direction.Left:
                        Left();
                        break;
                    case Direction.Right:
                        Right();
                        break;
                }
                
                return true;
            }
            return false;
        }

        public Direction OppositeDirection(Direction currDirection)
        {
            switch (currDirection)
            {
                case Direction.Up:
                    return Direction.Down;
                case Direction.Down:
                    return Direction.Up;
                case Direction.Left:
                    return Direction.Right;
                case Direction.Right:
                    return Direction.Left;
            }
            return Direction.None;
        }

        public void Forward()
        {
            Actuators[Direction.Up].MoveForward(this);
        }

        public void Back()
        {
            Actuators[Direction.Down].MoveForward(this);
        }

        public void Left()
        {
            Actuators[Direction.Left].MoveForward(this);
        }

        public void Right()
        {
            Actuators[Direction.Right].MoveForward(this);
        }
    }
}

/*
 * Implementation Invariants:
 * 
 * TranRobot class is a class that has inherited the Robot class. When initialized, it has 4 sensors and
 * 4 actuators. isValid recognizes which direction is next with priority to the direction that is not the
 * opposite of the current direction it is moving. This is to prevent the robot from moving backwards. This 
 * class has the capability for the robot to move forever, however it has been made to stop at the edge of
 * the maze. All functions are tied back to move() which will navigate the whole maze.
 */
