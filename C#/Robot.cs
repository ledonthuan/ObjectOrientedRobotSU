/* Robot.cs
* Don-Thuan Le
* CPSC3200
* Date: 5/8/2020
* version: 1.0
* 
* Class Invariants:
*When instantiated, the default position of the robot is 5,5, the grid is loaded in from the 
* command line, 1 sensor is instantiated towards Up, and one actuator is instantiated Up.
* 
* Interface Invariants:
* 
*/


using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class Robot
    {
        protected const int DEFAULT_POS = 5;
        protected bool State { get; set; }

        protected int PosR { get; set; }  //should be protected
        protected int PosC { get; set; }  //should be protected

        protected Dictionary<Direction, Sensor> Sensors { get; set; }
        protected Dictionary<Direction, Actuator> Actuators { get; set; }

        protected Grid MainGrid { get; set; }

        public Robot(string filePath)
        {
            this.State = true;
            this.PosR = DEFAULT_POS;
            this.PosC = DEFAULT_POS;

            Sensors = new Dictionary<Direction, Sensor>() { { Direction.Up, new Sensor(Direction.Up) } };
            Actuators = new Dictionary<Direction, Actuator>() { { Direction.Up, new Actuator(Direction.Up) } };

            MainGrid = Grid.Instance(filePath);
        }

        public Robot(string filePath, int PosR1, int PosC1)
        {
            this.State = true;
            this.PosR = PosR1;
            this.PosC = PosC1;

            Sensors = new Dictionary<Direction, Sensor>() { { Direction.Up, new Sensor(Direction.Up) } };
            Actuators = new Dictionary<Direction, Actuator>() { { Direction.Up, new Actuator(Direction.Up) } };

            MainGrid = Grid.Instance(filePath);
        }

        public void setGrid(Grid grid)
        {
            this.MainGrid = grid;
        }

        public virtual bool isValid()
        {
            if (IsPoweredup())
            {
                return Sensors[Direction.Up].IsValid(MainGrid, PosR, PosC);
            }
            return false;
        }

        public virtual void move()
        {
            while (moveOne()) ;
        }

        public virtual bool moveOne()
        {
            ChargeSensors();
            if (isValid())
            {
                Actuators[Direction.Up].MoveForward(this);
                return true;
            }
            return false;
        }

        public bool IsPoweredup()
        {
            return State;
        }

        // PreConditions:
        // PostConditions: Charges all sensors
        public void ChargeSensors()
        {
            foreach (var item in Sensors)
            {
                item.Value.Charge();
            }
        }

        public int getPosR()
        {
            return PosR;
        }
        public int getPosC()
        {
            return PosC;
        }
        public void setPosR(int pos)
        {
            PosR = pos;
        }
        public void setPosC(int pos)
        {
            PosC = pos;
        }
    }
}

/*
 * Implementation Invariants:
 * 
 * Robot is initialized automatically with one sensor and one actuator facing Up. And the 
 * default position is 5,5. IsValid calls the isvalid from the sensor to check the next
 * valid position. moveOne calls the MoveForward in the actuator. ChargeSensors is a function
 * that helps charge all the sensors so that the robot does not stop working in the middle 
 * of the maze.
 */
