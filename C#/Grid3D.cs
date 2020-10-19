/* Grid3D.cs
* Don-Thuan Le
* CPSC3200
* Date: 6/7/2020
* version: 1.0
* 
* Class Invariants:
* When instantiated, an array of grids is created.
* 
* Interface Invariants:
* There is a get grid function to return the 2D grid to put into robot
*/

using System;
namespace P5
{
    public class Grid3D
    {
        public Grid[] grids;

        public Grid3D(string[] filepaths)
        {
            grids = new Grid[filepaths.Length];
            for (int level = 0; level < grids.Length; level++)
            {
                grids[level] = new Grid(filepaths[level]);
            }
        }

        public Grid getGrid(int level)
        {
            return grids[level];
        }
    }
}

/*
 * Implementation Invariants:
 * Grid is an array of 2D grids to represent a 3D grid. Has a function to return the corret 2D grid to robot to navigate with
 */
