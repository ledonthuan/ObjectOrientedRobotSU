/* Actuator3D.cs
* Don-Thuan Le
* CPSC3200
* Date: 6/7/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, there is nothing to declare. This class acts as a way to change the grid depth that the submersible
* can move on.
* 
* Interface Invariants:
* There are only two functions that take in a submersible object to move the depth up or down the 3D grid 
*/

using System;
namespace P5
{
    public class Actuator3D
    {
        public Actuator3D()
        {
        }

        // PreConditions: 
        // PostConditions: allows submersible object to change current 3D grid level to go down
        public void MoveUp(Submersible R1)
        {
            if (R1.IsPoweredup() && (R1.getCurrentLevel() != 0))
            {
                R1.setCurrentLevel(R1.getCurrentLevel() - 1);
            }
        }

        // PreConditions: 
        // PostConditions: allows submersible object to change current 3D grid level to go up
        public void MoveDown(Submersible R1)
        {
            if (R1.IsPoweredup() && (R1.getCurrentLevel() != 10))
            {
                R1.setCurrentLevel(R1.getCurrentLevel() + 1);
            }
        }
    }
}

/*
 * Implementation Invariants:
 * 
 */
