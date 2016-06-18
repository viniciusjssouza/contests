
import java.util.*;
import java.io.*;

public class sum
{
    private static int n;

    public static void main(String[] args) throws FileNotFoundException, IOException
    {
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("in.txt")));
        //BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        while (true)
        {
            String line = in.readLine();
            if (line == null || line == "") break;
            StringTokenizer tokenizer = new StringTokenizer(line);
            if (!tokenizer.hasMoreTokens())
                break;
            n = Integer.parseInt(tokenizer.nextToken());
            int[][] input = new int[n][n];
            
            for (int i = 0; i < n; i++)
            {
                for (int k = 0 ;k < n; k++)
                {
                    if (tokenizer.hasMoreTokens())
                        input[i][k] = Integer.parseInt(tokenizer.nextToken());
                    else 
                    {
                        line = in.readLine();
                        tokenizer = new StringTokenizer(line);
                        input[i][k] = Integer.parseInt(tokenizer.nextToken());
                    }
                }
            }            
    /*
            for (int i = 0; i < n; i++)
            {
                for (int k =0; k < n; k++)
                    System.out.print(input[i][k] + " ");
                System.out.print('\n');
            }
    */
            System.out.println(getSomaMax(input));
            }
    }

    public static int getSomaMax(int[][] input)
    {
        int[][][][] somas = new int[n+1][n+1][n][n];
        int max = Integer.MIN_VALUE;
        for (int h = 1; h <= n; h++)
        {
            for (int l = 1; l <= n; l++)
            {
                //printf("\nSoma: h = %d l = %d\n", h, l);
                for (int i = 0; (i+h) <= n; i++)
                {
                    for (int k = 0; (k+l) <= n; k++)
                    {
                        if (l == 1 && h == 1)
                            somas[h][l][i][k] = input[i][k];
                        else if (l == 1)
                            somas[h][l][i][k] = somas[h-1][1][i][k] + somas[1][1][i+h-1][k];
                        else
                            somas[h][l][i][k] = somas[h][l-1][i][k] + somas[h][1][i][k+l-1];
                        if (somas[h][l][i][k] > max)
                            max = somas[h][l][i][k];
                        //printf("Para linha = %d col = %d, soma = %d \n", i, k, somas[h][l][i][k]);
                    }
                }
            }
        }
        return max;
    }
}