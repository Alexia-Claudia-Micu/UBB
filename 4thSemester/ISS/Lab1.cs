namespace lab1
{
    internal class Program
    {
        /*
           1. Write a program that finds the length of the longest substring without repeating
            characters in a given string. For example, the longest substring without repeating letters
            in "abcabcbb" is "abc", with a length of 3.
         */
        static void Main(string[] args)
        {
            /*
             * my_string - given string
             * length: integer memorising the current length
             * max_length: integer memorising the maximum length until that point
             * apparitions: array counting the number of apparitions of each letter in that substring (never surpasses 1)
             */
            string my_string = "abcabcbb";
            int length = 0, max_length=0;
            int[] apparitions = new int[30];
            for(int letter = 0; letter < my_string.Length; letter++)
            {
                int index_of_letter = my_string[letter].CompareTo('a');

                if (apparitions[index_of_letter] == 0)
                {
                    length++;
                    if (length > max_length)
                        max_length = length;
                    apparitions[index_of_letter]++;
                }
                else
                {
                    length = 0;
                    clear_apparitions(apparitions);
                }
            }
            Console.WriteLine(max_length);
        }

        static void clear_apparitions(int[] apparitions)
        {
            /*
             * zeroes every value from apparitions
             */
            for (int iterator = 0; iterator < 30; iterator++)
                apparitions[iterator] = 0;
        }

    }
}