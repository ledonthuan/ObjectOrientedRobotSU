 /* Sensor.cs
 * Don-Thuan Le
 * CPSC3200
 * Date: 5/8/2020
 * version: 1.0
 * 
 * 
 * Class Invariants:
 * When instantiated, the battery level will be at 100%, the state will be on, the discharge rate
 * will be randomly selected from 1 to 1000, and - if not specified - the direction of the sensor
 * will be Up. 
 * 
 */ 


using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace P5
{
    public class Sensor
    {
        protected bool State { get; set; }
        private uint BatteryLevel { get; set; }
        private uint DischargeRate { get; set; }
        protected Direction SensorDirection { get; set; }

        public Sensor()
        {
            Random rnd = new Random();

            State = true;
            BatteryLevel = 1000;
            DischargeRate = (uint)rnd.Next(1, 1001);
            SensorDirection = Direction.Up;
        }

        public Sensor(Direction senDirection)
        {
            Random rnd = new Random();

            State = true;
            BatteryLevel = 1000;
            DischargeRate = (uint)rnd.Next(1, 1001);
            SensorDirection = senDirection;
        }

        public Sensor(uint rate)
        {
            State = true;
            BatteryLevel = 1000;
            DischargeRate = rate;
            SensorDirection = Direction.Up;
        }

        // PreConditions: New DIrection for sensor to go in
        // PostConditions: Direction of sensor is changed respectively
        public void SetSensorDirection(Direction newDirection)
        {
            SensorDirection = newDirection;
        }
        
        public bool IsValid(Grid mainGrid, int posR, int posC)
        {
            if (State)
            {
                if (BatteryLevel < DischargeRate)
                    return false;
                else if (BatteryLevel < 100)
                {
                    State = false;
                    return false;
                }
                else
                {
                    BatteryLevel -= DischargeRate;
                    switch (SensorDirection)
                    {
                        case Direction.Up:
                            return mainGrid.isPath(posR - 1, posC);
                        case Direction.Down: 
                            return mainGrid.isPath(posR + 1, posC);
                        case Direction.Left:
                            return mainGrid.isPath(posR, posC - 1);
                        case Direction.Right:
                            return mainGrid.isPath(posR, posC + 1);
                    }
                }
            }
            return false;
        }

        // PreConditions: 
        // PostConditions: Battery is set back to 1000
        public void Charge()
        {
            if (BatteryLevel != 1000)
            {
                State = true;
                BatteryLevel = 1000;
                Thread.Sleep(2000);
                return;
            }
        }

        // PreConditions: direction for sensor to turn to
        // PostConditions: sensor direction is adjusted respectively
        public Direction SensorRotate(string turn)
        {
            turn.ToLower();

            switch (SensorDirection)
            {
                case Direction.Up:
                    if (turn == "right")
                    {
                        SensorDirection = Direction.Right;
                    }
                    else if (turn == "left")
                    {
                        SensorDirection = Direction.Left;
                    }
                    break;
                case Direction.Right:
                    if (turn == "right")
                    {
                        SensorDirection = Direction.Down;
                    }
                    else if (turn == "left")
                    {
                        SensorDirection = Direction.Up;
                    }
                    break;
                case Direction.Down:
                    if (turn == "right")
                    {
                        SensorDirection = Direction.Left;
                    }
                    else if (turn == "left")
                    {
                        SensorDirection = Direction.Right;
                    }
                    break;
                case Direction.Left:
                    if (turn == "right")
                    {
                        SensorDirection = Direction.Up;
                    }
                    else if (turn == "left")
                    {
                        SensorDirection = Direction.Down;
                    }
                    break;
            }
            return SensorDirection;
        }

        public uint getBatteryLevel()
        {
            return BatteryLevel;
        }

    }
}

/*
 * Implementation Invariants:
 * 
 * The isValid function calls the isPath function from the Grid class to verify that the next spot
 * is a valid move. The SensorRotate function is added for the RotatingRobot class to be able to change 
 * the directions of the sensors when the robot has rotated. This cannot be achieved in the RotatingRobot
 * itself.
 */
