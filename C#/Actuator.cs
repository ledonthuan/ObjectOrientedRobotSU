/* Actuator.cs
* Don-Thuan Le
* CPSC3200
* Date: 5/8/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, the state is on and - if not specified - the direction is Up.
* 
* Interface Invariants:
* All parameters are either private or protected and cannot be publicly accessed unless by inherited 
* class. 
*/


using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class Actuator
    {
        private bool State; //THIS IS UNNECESSARY
        private Direction ActuatorDirection;

        public Actuator()
        {
            State = true;
            ActuatorDirection = Direction.Up;
        }

        public Actuator(Direction actDirection)
        {
            State = true;
            ActuatorDirection = actDirection;
        }

        // PreConditions: 
        // PostConditions: Robot position is adjusted to the position it wants to go in
        public void MoveForward(Robot R1)
        {
            if (R1.IsPoweredup())
            {
                switch (ActuatorDirection)
                {
                    case Direction.Up:
                        if (R1.getPosR() != 0)
                            R1.setPosR(R1.getPosR()-1);
                        break;
                    case Direction.Down:
                        if (R1.getPosR() != 10)
                            R1.setPosR(R1.getPosR() + 1);
                        break;
                    case Direction.Left:
                        if (R1.getPosC() != 0)
                            R1.setPosC(R1.getPosC() - 1);
                        break;
                    case Direction.Right:
                        if (R1.getPosC() != 10)
                            R1.setPosC(R1.getPosC() + 1);
                        break;
                }
            }
        }

        public Direction getDirection()
        {
            return ActuatorDirection;
        }

        // PreConditions: direction for actuator to turn to
        // PostConditions: Direction of actuator is adjusted to respective direction
        public Direction ActuatorRotate(string turn)
        {
            turn.ToLower();

            switch (ActuatorDirection)
            {
                case Direction.Up:
                    if (turn == "right")
                    {
                        ActuatorDirection = Direction.Right;
                    }
                    else if (turn == "left")
                    {
                        ActuatorDirection = Direction.Left;
                    }
                    break;
                case Direction.Right:
                    if (turn == "right")
                    {
                        ActuatorDirection = Direction.Down;
                    }
                    else if (turn == "left")
                    {
                        ActuatorDirection = Direction.Up;
                    }
                    break;
                case Direction.Down:
                    if (turn == "right")
                    {
                        ActuatorDirection = Direction.Left;
                    }
                    else if (turn == "left")
                    {
                        ActuatorDirection = Direction.Right;
                    }
                    break;
                case Direction.Left:
                    if (turn == "right")
                    {
                        ActuatorDirection = Direction.Up;
                    }
                    else if (turn == "left")
                    {
                        ActuatorDirection = Direction.Down;
                    }
                    break;
            }
            return ActuatorDirection;
        }
    }
}


/*
 * Implementation Invariants:
 * 
 * The MoveForward function takes in the robot object and changes the position of the robot
 * if it decides to move in the direction of the actuator. The ActuatorRotate function is
 * used by the RotatingRobot to change the direction of the actuator to the direction of
 * the robot.
 */ 