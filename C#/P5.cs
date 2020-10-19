/* .cs
* Don-Thuan Le
* CPSC3200
* Date: 5/8/2020
* version: 1.0
* 
* Overview: This driver demonstrates three different types of robots, one that only moves up, one that roates to move, and
* one that does not change the direction that it is facing but can move in all four directions. With the robot class, you can only move up 
* and the robot will get stuck at the beginning of the maze. With the rotating robot class you are able to reach the end of the maze and 
* it will stop. With trans robot class, you are able to reach the end of the maze, but the robot has the potential to continue forever 
* if adjusted to do so. 
*/

using System;
using System.Collections.Generic;
using System.IO;

namespace P5
{
    class P5
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                System.Console.WriteLine("Please enter a valid grid file location.");
                return;
            }

            var gridFiles = Directory.GetFiles(args[0]);

            List<Robot> robots = new List<Robot>();
            var subRotatingRobot = new SubRotatingRobot(gridFiles);
            robots.Add(subRotatingRobot);

            //var R1 = new Robot(args[0]);
            //var R2 = new RotatingRobot(args[0]);
            //var R3 = new TranRobot(args[0]);

            //robots.Add(R1);
            //robots.Add(R2);
            //robots.Add(R3);

            foreach (var robot in robots)
            {
                robot.move();
            }

        }
    }
}
