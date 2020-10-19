/* Sensor3D.cs
* Don-Thuan Le
* CPSC3200
* Date: 6/7/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, the state is on and - if not specified - the direction is Up.
* 
* Interface Invariants:
* All parameters are either private or protected and cannot be publicly accessed unless by inherited 
* class. 
*/

using System.Threading;
using System;
namespace P5
{
    public class Sensor3D
    {
        protected bool State { get; set; }
        private uint BatteryLevel { get; set; }
        private uint DischargeRate { get; set; }
        protected Direction3D SensorDirection { get; set; }

        public Sensor3D()
        {
            Random rnd = new Random();

            State = true;
            BatteryLevel = 1000;
            DischargeRate = (uint)rnd.Next(1, 1001);
            SensorDirection = Direction3D.LevelDown;
        }

        public Sensor3D(Direction3D senDirection)
        {
            Random rnd = new Random();

            State = true;
            BatteryLevel = 1000;
            DischargeRate = (uint)rnd.Next(1, 1001);
            SensorDirection = senDirection;
        }

        // PreConditions: 
        // PostConditions: Changes battery level (discharges)
        public bool isValid(Grid3D grid3D, int posR, int posC, int level)
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
                        case Direction3D.LevelDown:
                            if (level == 10)
                                return false;
                            Grid temp = grid3D.getGrid(level + 1);
                            return temp.isPath(posR, posC);
                        case Direction3D.LevelUp:
                            if (level == 0)
                                return false;
                            Grid temp2 = grid3D.getGrid(level - 1);
                            return temp2.isPath(posR, posC);
                    }
                }
            }
            return false;
        }

        // PreConditions: 
        // PostConditions: changes battery level back to 1000
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


    }
}
/*
 * Implementation Invariants:
 * Sensor senses down before it senses up. Once it reaches the bottom it has the potential of just bouncing between the bottom and the second to bottom floor.
 */
