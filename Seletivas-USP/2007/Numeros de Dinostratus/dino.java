/***********************************************************
 * Numeros de Dinostratus - Seletivas IME-USP - 2007
 *
 * Autor: Vinicius J. S. Souza
 * Data: 05/02/2010
 * Tecnicas: fatoracao
 */


import java.util.*;
import java.io.*;

public class dino
{
    public static void main(String args[]) throws Exception
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int instancia = 0;
        while (true)
        {
            String line = br.readLine();
            if (line == null || line.length() == 0)
                break;
            if (instancia > 0)
                System.out.println();
            HashMap<Integer, Integer> primes = factor(Integer.parseInt(line));
            int size = primes.size();
            Set<Integer> keys = primes.keySet();
            int[] a = new int[size];
            boolean isDino = true;
            boolean has2 = false;
            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;
            for (int key : keys)
            {
                if (size == 1 && primes.get(key) < 8)
                {
                    isDino = false;
                    break;
                }
                else if (size == 2)
                {
                    int x = primes.get(key);
                    if (x > max)
                        max = x;
                    if (x < min)
                        min = x;
                }
                else if (size == 3)
                {
                    int x = primes.get(key);
                    if (x < 1)
                        break;
                    if (x > 1)
                        has2 = true;
                }
            }
            if (size == 2)
            {
                if (min == 1 && max < 5)
                    isDino = false;
            }
            else if (size == 3 && !has2)
                isDino = false;
            System.out.printf("Instancia %d\n%s\n", ++instancia, isDino == true ? "sim" : "nao");
        }
    }
    /************* Obtendo primos de um numero ***********************************/
    public static HashMap<Integer, Integer> factor(int n)
    {
         HashMap<Integer, Integer> M = new HashMap<Integer, Integer>();
         if (n < 0) return factor(-n);
         if (n < 2) return M;
         n = squeeze(M, n, 2);
         n = squeeze(M, n, 3);
         int maxP = (int)Math.sqrt(n) + 2;
         for (int p = 5; p < maxP; p += 6) {
            n = squeeze(M, n, p);
            n = squeeze(M, n, p+2);
         }
         if (n > 1)
         {
            Integer x = M.get(n);
            if (x == null)
                M.put(n, 1);
            else
                M.put(n, x+1);
         }
         return M;
    }
    static int squeeze(HashMap<Integer, Integer> M, int n, int p)
    {
        for (; n % p == 0; n /= p)
        {
            Integer x = M.get(p);
            if (x == null)
                M.put(p, 1);
            else
                M.put(p, x+1);
        }
        return n;
    }
}
