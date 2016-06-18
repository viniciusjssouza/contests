using System;

public class SubPrime
{
    static int N, B;
    static long[] banks = new long[30];
    static void Main(string[] args)
    {
        while (true)
        {
            string[] line = Console.ReadLine().Split(' ');
            B = int.Parse(line[0]);
            N = int.Parse(line[1]);
            if (B == 0 && N == 0)
                break;
            line = Console.ReadLine().Split(' ');
            for (int k = 0; k < line.Length; k++)
            {
                banks[k + 1] = long.Parse(line[k]); 
            }
            for (int i = 0; i < N; i++)
            {
                line = Console.ReadLine().Split(' ');
                int dev = int.Parse(line[0]);
                int cred = int.Parse(line[1]);
                long v = long.Parse(line[2]);
                banks[dev] -= v;
                banks[cred] += v;
            }
            bool ok = true;
            for (int i = 1; i <= B; i++)
            {
                if (banks[i] < 0)
                {
                    ok = false;
                    break;
                }
            }
            Console.WriteLine("{0}", ok == true? 'S' : 'N');
        }
    }
}
