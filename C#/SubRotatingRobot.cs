/* SubRotatingRobot.cs
* Don-Thuan Le
* CPSC3200
* Date: 6/7/2020
* version: 1.0
* 
* Class Invariants:
* inheriting from Rotating Robot, you have the same functionality but with the added functionality of submersible to navigate 3D.
* calling moveOne() just move one grid or rotates.
* 
* Interface Invariants:
* This is a class that is an upgraded Rotating Robot to allow 3D grid navigation.
* SubRotatingRobot cannot rotate 180 degrees, can only turn 90 degrees to the left or 90 degrees to the right. Move one
* either rotates the robot or moves the robot. Robot will never go back the way it came from. AFter reaching the end of one level,
* it will drop down to the next level.
*/

using System;
namespace P5
{
    public class SubRotatingRobot : RotatingRobot
    {
        private bool state = true;
        private Submersible submersible;

        public SubRotatingRobot(string [] filepath) : base(filepath[0])
        {
            if (filepath.Length != 11)
                return;
            Grid3D grid = new Grid3D(filepath);
            submersible = new Submersible(grid);
        }

        public override void move()
        {
            while (this.moveOne());
        }

        public override bool moveOne()
        {
            foreach (var sensor3DPair in this.submersible.getSensors3D())
                sensor3DPair.Value.Charge();

            this.setGrid(submersible.getCurrentDepthGrid());
            this.syncPositions();
            return base.moveOne() || submersible.moveOne();
        }

        // PreConditions: 
        // PostConditions: syncs the row and column position of the Rotating Robot to that of the Submersible.
        private void syncPositions()
        {
            this.submersible.setPosR(this.getPosR());
            this.submersible.setPosC(this.getPosC());
        }
    }
}

/*
 * Implementation Invariants:
 * inherits Rotating Robot. submersible is "inherited" as an object within creating a has-a relationship. 
 * 
 */
