/* Submersible.cs
* Don-Thuan Le
* CPSC3200
* Date: 6/7/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, there is nothing to declare. Like the Robot class, the state is true, it has an actuator that moves up and down, a sensor to sense up and one to sense down.
* It has a 3D grid which is an array of 2D grids. 
* 
* Interface Invariants:
* There are only two functions that take in a submersible object to move the depth up or down the 3D grid 
*/
using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class Submersible
    {
        protected const int DEFAULT_POS = 5;
        protected bool state;
        protected Dictionary<Direction3D, Sensor3D> Sensors { get; set; }
        protected Actuator3D Actuator { get; set; }
        protected Grid3D Grid3D { get; set; }
        protected int CurrentLevel { get; set; }
        protected int posR;
        protected int posC;

        public Submersible(Grid3D grid3D)
        {
            state = true;
            Sensors = new Dictionary<Direction3D, Sensor3D>() { { Direction3D.LevelDown, new Sensor3D() }, { Direction3D.LevelUp, new Sensor3D(Direction3D.LevelUp) } };
            this.Actuator = new Actuator3D();
            this.Grid3D = grid3D;
            CurrentLevel = 0;
            posR = DEFAULT_POS;
            posC = DEFAULT_POS;
        }

        public Grid getCurrentDepthGrid()
        {
            return this.Grid3D.getGrid(this.CurrentLevel);
        }

        public bool IsPoweredup()
        {
            return state;
        }

        public bool isValid(Direction3D direction3D)
        {
            return Sensors[direction3D].isValid(Grid3D, posR, posC, CurrentLevel);
        }

        // PreConditions: 
        // PostConditions: changes the level of the grid that the submersible is on by calling actuator
        public bool moveOne()
        {
            if (isValid(Direction3D.LevelDown))
            {
                Actuator.MoveDown(this);
                return true;
            }

            if (isValid(Direction3D.LevelUp))
            {
                Actuator.MoveUp(this);
                return true;
            }

            return false;
        }

        public void move()
        {
            while (moveOne()) ;
        }

        public int getCurrentLevel()
        {
            return CurrentLevel;
        }

        // PreConditions: 
        // PostConditions: allows change of current level of the submersible on the grid
        public void setCurrentLevel(int setlevel)
        {
            CurrentLevel = setlevel;
        }

        public int getPosR()
        {
            return posR;
        }
        public int getPosC()
        {
            return posC;
        }
        public void setPosR(int pos)
        {
            posR = pos;
        }
        public void setPosC(int pos)
        {
            posC = pos;
        }

        public Dictionary<Direction3D, Sensor3D> getSensors3D()
        {
            return Sensors;
        }
    }
}

/*
 * Implementation Invariants:
 * sensor is a dictionary of sensors and there is just one actuator to move up and down. 3D grid is an array of 2D grids. 
 * 
 */
