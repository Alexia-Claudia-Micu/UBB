
using System;

namespace Lab3
{
    public static class Program
    {
        public static void Main(string[] args)
        {
            Run("p1.txt");
            Run("p2.txt");
            Run("p3.txt");
            Run("p1err.txt");
        }

        private static void Run(string filePath)
        {
            Scanner scanner = new Scanner(filePath);
            scanner.Scan();
            PrintToFile(filePath.Replace(".txt", "IT.txt"), scanner.getIdentifierTable());
            PrintToFile(filePath.Replace(".txt", "CT.txt"), scanner.getConstantTable());
            PrintToFile(filePath.Replace(".txt", "PIF.txt"), scanner.getPif());
        }


        private static void PrintToFile(string filePath, object obj)
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(filePath))
                {
                    writer.WriteLine(obj);
                }
            }
            catch (FileNotFoundException e)
            {
                Console.WriteLine(e);
            }
        }
    }
}
