/* RotatingRobot.cs
* Don-Thuan Le
* CPSC3200
* Date: 5/8/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, 3 sensors are made (up, left and right), 1 actuator is made(up), the starting position is 
* 5,5, the grid is loaded in from the command line and the robot direction is Up.
* 
* Interface Invariants:
* RotatingRobot cannot rotate 180 degrees, can only turn 90 degrees to the left or 90 degrees to the right. Move one
* either rotates the robot or moves the robot. Robot will never go back the way it came from, it will stop at the edge
* of the maze.
*/


using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class RotatingRobot : Robot
    {
        private string Next;
        protected Direction RobotDirection;

        public RotatingRobot(string filePath) : base(filePath)
        {
            RobotDirection = Direction.Up;
            Sensors[Direction.Left] = new Sensor(Direction.Left);
            Sensors[Direction.Right] = new Sensor(Direction.Right);
        }

        public RotatingRobot(string filePath, int posR1, int posC1) : base(filePath)
        {
            PosR = posR1;
            PosC = posC1;
            RobotDirection = Direction.Up;
            Sensors[Direction.Left] = new Sensor(Direction.Left);
            Sensors[Direction.Right] = new Sensor(Direction.Right);
        }

        public override bool isValid()
        {
            if (IsPoweredup())
            {
                foreach (var item in Sensors)
                {
                    if (item.Value.IsValid(MainGrid, PosR, PosC))
                    {
                        Next = NextDirection(item.Key);
                        return true;
                    }
                }
            }
            return false;
        }

        public string NextDirection(Direction directionTo)
        {
            switch (RobotDirection)
            {
                case Direction.Up:
                    if (directionTo == Direction.Left)
                        return "left";
                    else if (directionTo == Direction.Right)
                        return "right";
                    break;
                case Direction.Down:
                    if (directionTo == Direction.Left)
                        return "right";
                    else if (directionTo == Direction.Right)
                        return "left";
                    break;
                case Direction.Left:
                    if (directionTo == Direction.Up)
                        return "right";
                    else if (directionTo == Direction.Down)
                        return "left";
                    break;
                case Direction.Right:
                    if (directionTo == Direction.Up)
                        return "left";
                    else if (directionTo == Direction.Down)
                        return "right";
                    break;
            }
            if (RobotDirection == directionTo)
                return "straight";
            return null;
        }

        public override void move()
        {
            while (moveOne())
            {
                Console.WriteLine($"rotating robot x:{this.getPosR()} y:{this.getPosC()}");
            }
        }

        public override bool moveOne()
        {
            ChargeSensors();
            if (isValid())
            {
                switch (Next)
                {
                    case "left":
                        rotate(Next);
                        break;
                    case "right":
                        rotate(Next);
                        break;
                    case "straight":
                        Actuators[RobotDirection].MoveForward(this);
                        break;
                }
                return true;
            }
            return false;
        }

        // PreConditions: Direction for robot to turn to
        // PostConditions: Robot Direction is changed respectively
        public void rotate(string turn)
        {
            turn.ToLower();

            switch (RobotDirection)
            {
                case Direction.Up:
                    if (turn == "right")
                    {
                        RobotDirection = Direction.Right;
                    }
                    else if (turn == "left")
                    {
                        RobotDirection = Direction.Left;
                    }
                    break;
                case Direction.Right:
                    if (turn == "right")
                    {
                        RobotDirection = Direction.Down;
                    }
                    else if (turn == "left")
                    {
                        RobotDirection = Direction.Up;
                    }
                    break;
                case Direction.Down:
                    if (turn == "right")
                    {
                        RobotDirection = Direction.Left;
                    }
                    else if (turn == "left")
                    {
                        RobotDirection = Direction.Right;
                    }
                    break;
                case Direction.Left:
                    if (turn == "right")
                    {
                        RobotDirection = Direction.Up;
                    }
                    else if (turn == "left")
                    {
                        RobotDirection = Direction.Down;
                    }
                    break;
            }

            var SensorsTemp = new Dictionary<Direction, Sensor>();

            foreach (var item in Sensors)
            {
                var direction = item.Value.SensorRotate(turn);
                SensorsTemp[direction] = item.Value;
            }
            Sensors = SensorsTemp;

            var ActuatorsTemp = new Dictionary<Direction, Actuator>();

            foreach (var item in Actuators)
            {
                var direction = item.Value.ActuatorRotate(turn);
                ActuatorsTemp[direction] = item.Value;
            }
            Actuators = ActuatorsTemp;
        }

        public Direction getRobotDirection()
        {
            return RobotDirection;
        }
    }
}

/*
 * Implementation Invariants:
 * 
 * RotatingRobot is a class that has inherited the Robot class. When initialized, it has 3 
 * sensors (up, left, and right) and there is one actuator still (up). Overrided isValid helps
 * identify which direction is next from the three sensors. One identified, the robot rotates 
 * to that direction and the sensors and actuator rotate accordingly to continue the maze. In the 
 * moveOne function, rotate is counted is one move.
 */
