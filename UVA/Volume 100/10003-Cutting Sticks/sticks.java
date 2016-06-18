import java.awt.Point;
import java.io.*;
import java.util.*;

public class sticks
{
    static int minimo;
    static int SIZE, N;

    public static void main(String args[]) throws IOException
    {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        while (true)
        {
            minimo = Integer.MAX_VALUE;
            SIZE = Integer.parseInt(input.readLine());
            if (SIZE == 0) break;
            N = Integer.parseInt(input.readLine());
            int[] cuts = new int[N];
            StringTokenizer tk = new StringTokenizer(input.readLine());
            for (int i = 0; i < N; i++)
                cuts[i] = Integer.parseInt(tk.nextToken());
            HashMap<Point, Integer> memory = new HashMap<Point, Integer>();
            for (int i = 0; i < N; i++)
            {
                int result = backtrack(cuts, memory, 0, cuts[i]) +
                        backtrack(cuts, memory, cuts[i], SIZE);
                if (result < minimo)
                    minimo = result;
            }
            System.out.printf("The minimum cutting is %d.%n", (minimo + SIZE));
        }
    }

    static int backtrack(int[] cuts, Map<Point, Integer> memory, int inf, int sup)
    {
        //System.out.println("Chamando para " + inf + " e " + sup);
        int minimoLocal = Integer.MAX_VALUE;
        int i = lSearch(cuts, inf+1);
        //System.out.println("bsearch: de " + (inf+1) + "=" + i);
        for (; i < N && cuts[i] < sup; i++)
        {
            Integer a = memory.get(new Point(inf,cuts[i]));
            if (a == null)
                a = backtrack(cuts, memory, inf, cuts[i]);
            Integer b =	memory.get(new Point(cuts[i], sup));
            if (b == null)
                b = backtrack(cuts, memory, cuts[i], sup);
            int result = a + b + (sup - inf);
            if (result < minimoLocal)
                    minimoLocal = result;
        }
        if (minimoLocal == Integer.MAX_VALUE)
        {
            memory.put(new Point(inf, sup), 0);
            return 0;
        }
        memory.put(new Point(inf, sup), minimoLocal);
        return minimoLocal;
    }

    static int lSearch(int[] cuts, int x)
    {
        for (int i = 0; i < N; i++)
            if (cuts[i] >= x)
                return i;
        return N;
    }

    static int bsearch(int[] cuts, int x, int inf, int sup)
    {
        if (sup - inf == 1)
        {
            if (x > cuts[sup] && sup + 1 < N) return sup+1;
            else if (x <= cuts[inf]) return inf;
            else return sup;
        }
        else if (sup == inf)
        {
            if (cuts[sup] < x || sup+1 < N)
                return sup+1;
            else return sup;
        }

        int half = (sup+inf) / 2;
        if (x < cuts[half])
            return bsearch(cuts, x, inf, half-1);
        else if (x > cuts[half])
            return bsearch(cuts, x, half+1, sup);
        else
            return half;
    }
}

