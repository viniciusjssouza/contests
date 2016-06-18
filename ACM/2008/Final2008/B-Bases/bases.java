/*************************************************************
 * Bases - Final Sul-americana 2008
 *
 * Autor: Vinicius J. S. Souza
 * Data: 20/08/2009
 * Tecnicas utilizadas: teoria dos numeros e solucao de equacoes algebricas
 ***************************************************************/

import java.util.*;
import java.io.*;

public class bases
{
    private static final int TAM = 17;
    private static long maxDigit = 2;

    public static void main(String args[]) throws IOException
    {
        //long time = System.currentTimeMillis();
        BufferedReader input = new BufferedReader(
                new InputStreamReader(System.in));
        while (true)
        {
            String line = input.readLine();
            if (line.equals("="))
                break;
            maxDigit = 2;
            StringTokenizer tokenizer = new StringTokenizer(line, "=", false);
            String op1 = tokenizer.nextToken();
            String op2 = tokenizer.nextToken();
            long[] leftCoefs = solveExpr(op1);
            long[] rightCoefs = solveExpr(op2);

            boolean isInfinito = true;
            int grau = 0;
            int a0 = -1;
            for (int i = 0; i < TAM; i++)
            {
                leftCoefs[i] = leftCoefs[i] - rightCoefs[i];
                if (a0 < 0 && leftCoefs[i] != 0)
                    a0 = i;
                if (i > 0 && leftCoefs[i] != 0)
                {
                     isInfinito = false;
                     grau = i;
                }
            }
            if (isInfinito)
            {
                if (leftCoefs[0] == 0)
                    System.out.println(maxDigit + "+");
                else
                    System.out.println('*');
                continue;
            }
            Set<Long> divAo = getDivisores(Math.abs(leftCoefs[a0]));
            Set<Long> divAn = getDivisores(Math.abs(leftCoefs[grau]));

            Set<Long> result = new TreeSet<Long>();
            for (long p : divAo)
            {
                for (long q : divAn)
                {
                    double div = p / q;
                    long possibleRoot = (long) div;
                    if (Math.ceil(div) == Math.floor(div) && possibleRoot >= maxDigit &&
                            isRaiz(leftCoefs, possibleRoot))
                        result.add(possibleRoot);
                }
            }

            if (result.size() == 0)
                System.out.print('*');
            boolean isInit = true;
            for (long l : result)
            {
                if (!isInit)
                    System.out.print(' ');
                else isInit = false;
                System.out.print(l);
            }
            System.out.println(); 
        }
        //System.out.println((double)(System.currentTimeMillis()-time) / 1000.0);
    }

    public static Set<Long> getDivisores(long x)
    {
         Set<Long> primos = new HashSet<Long>();
         Set<Long> divisores = new HashSet<Long>();
         long i;                 /* counter */
         long c;                 /* remaining product to factor */
         c = x;
         if (x == 0)
             return divisores;
         while ((c % 2) == 0)
         {
             primos.add(Long.valueOf(2));
             c = c / 2;
         }
         i = 3;
         while (i <= (Math.sqrt(c)+1))
         {
                if ((c % i) == 0)
                {
                        primos.add(i);
                        c = c / i;
                }
                else
                        i = i + 2;
        }
        if (c > 1)
            primos.add(c);
         primos.add(Long.valueOf(1));
         geraDivisores(primos, divisores, 1, x);
         divisores.add(Long.valueOf(x));
         return divisores;
    }

    public static void geraDivisores(Set<Long> primos, Set<Long> divisores, long result, long num)
    {
        for (long l : primos)
        {
            long x = result * l;
            if (x <= num && !divisores.contains(x) && (num % x) == 0)
            {
                divisores.add(x);
                geraDivisores(primos, divisores, x, num);
            }
        }
    }

    public static boolean isRaiz(long[] coef, long b)
    {
        long result = 0;
        for (int i = 0; i < TAM; i++)
            result += (Math.pow(b,i)*coef[i]);
        return (result == 0);
    }

    public static long[] solveExpr(String expr)
    {
        int ptr = 0;
        long[] coef = new long[TAM];
        initCoefs(coef);
        while (ptr < expr.length())
        {
            int inf = ptr;
            ptr = markNextNum(expr, ptr);
            if (ptr >= expr.length() || expr.charAt(ptr) == '+')
            {                
                for (int i = ptr-1, exp = 0; i >= inf; i--, exp++)
                {
                    long digit = expr.charAt(i) - '0';
                    coef[exp] += digit;
                    if (digit+1 > maxDigit)
                        maxDigit = digit+1;
                }
            }
            else if (expr.charAt(ptr) == '*')
            {
                long[] numA = new long[TAM];
                initCoefs(numA);
                for (int i = ptr-1, exp = 0; i >= inf; i--, exp++)
                {
                    int digit = expr.charAt(i) - '0';
                    numA[exp] = digit;
                    if (digit+1 > maxDigit)
                        maxDigit = digit+1;
                }
                while (ptr < expr.length() && expr.charAt(ptr) == '*')
                {
                    ptr++;
                    inf = ptr;
                    ptr = markNextNum(expr, ptr);

                    long[] numB = new long[TAM];
                    long[] result = new long[TAM];
                    initCoefs(result);
                    initCoefs(numB);
                    for (int i = ptr-1, exp = 0; i >= inf; i--, exp++)
                    {
                        int digit = expr.charAt(i) - '0';
                        numB[exp] = digit;
                        if (digit+1 > maxDigit)
                            maxDigit = digit+1;
                    }
                    for (int i = 0; i < TAM; i++)
                        for (int k = 0; k < TAM; k++)
                        {
                            if (i+k < TAM)
                                result[i+k] += (numA[i]*numB[k]);
                        }
                    numA = result;
                }
                for (int i = 0; i < TAM; i++)
                    coef[i] += numA[i];
            }
            ptr++;
        }
        return coef;
    }

    public static void initCoefs(long[] coef)
    {
        for (int i = 0; i < coef.length; i++)
            coef[i] = 0;
    }

    public static int markNextNum(String expr, int ptr)
    {
        for (; ptr < expr.length() && Character.isDigit(expr.charAt(ptr));
                ptr++)
            {}
        return ptr;
    }
}
