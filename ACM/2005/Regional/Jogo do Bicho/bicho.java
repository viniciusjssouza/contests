import java.io.*;
import java.util.*;

public class bicho
{
    static int N, M;
    static double V;
    public static void main(String[] args) throws IOException
    {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        while (true)
        {
            StringTokenizer t = new StringTokenizer(input.readLine());
            V = Double.parseDouble(t.nextToken());
            N = Integer.parseInt(t.nextToken());
            M = Integer.parseInt(t.nextToken());
            if (V == 0 && N == 0 && M == 0)
                  break;
            double premio = 0;
            if (N % 10000 == M % 10000)
                premio = (V * 3000.0);
            else if (N % 1000 == M % 1000)
                premio = V * 500;
            else if (N % 100 == M % 100)
                premio = (V * 50);
            else
            {
                int x = N % 100;
                if (x == 0)
                    x = 100;
                int div = M % 100;
                if (div == 0)
                    div = 100;
                while ( (div % 4) != 0)
                    div++;
                if (Math.abs(div - x) < 4)
                    premio = V * 16;
            }
            System.out.printf("%.2f\n", premio);
        }
    }
}