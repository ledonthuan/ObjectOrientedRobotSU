using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace P5
{
    public class Grid
    {
        private int[,] Array;
        private static Grid _instance;

        public Grid(string filePath)
        {
            Array = new int[11, 11];
            using (StreamReader sr = new StreamReader(filePath))
            {
                string line;
                // Read and display lines from the file until the end of
                // the file is reached.
                int rowCount = 0;
                while ((line = sr.ReadLine()) != null)
                {
                    var row = line.Split(" ");
                    for (int column = 0; column < 11; column++)
                    {
                        // add error handling
                        this.Array[rowCount, column] = int.Parse(row[column]);
                    }
                    rowCount++;
                }
            }
        }

        public static Grid Instance(string filePath)
        {
            if (_instance == null)
                _instance = new Grid(filePath);
            return _instance;
        }

        public bool isPath(int row, int col)
        {
            if (row < 0 || row > 10 || col < 0 || col > 10)
                return false;

            return Array[row, col] == 1 ? true : false;
        }
    }
}
