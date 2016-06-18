using System;

public class Lua
{
    static int N, M;
    static int[] data = new int[10010];
    static void Main(string[] args)
    {
        int tcase = 1;
        while (true)
        {
            string[] line = Console.ReadLine().Split();
            N = int.Parse(line[0]);
            M = int.Parse(line[1]);
            if (N == 0 && M == 0)
                break;
            for (int i = 0; i < N; i++)
            {
                data[i] = int.Parse(Console.ReadLine());
            }
            double soma = 0;
            
            for (int i = 0; i < M; i++)
            {
                soma += data[i];
            }
            double media = soma / (double)M;
            double max = media, min = media;
            for (int i = 1; (i+M-1) < N; i++) {
                media = (double)(M * media - data[i - 1] + data[i + M - 1]) / (double)M;
                max = Math.Max(max, media);
                min = Math.Min(min, media);
            }
            Console.Write("Teste {0}\n{1} {2}\n\n", tcase++, (int)min, (int)max);
        }
    }
}
