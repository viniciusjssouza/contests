import java.io.FileNotFoundException;
import java.util.*;
import java.math.*;

public class light
{
    public static void main(String args[]) throws FileNotFoundException
    {
        final int MAXN =  20000;
        //Scanner input = new Scanner(System.in);
        Scanner input = new Scanner(new java.io.File("in.txt"));
        int i,j; /* counters */

        long[][] bc = new long[MAXN][4]; /* table of binomial coefficients */
        for (i=0; i<=MAXN-1; i++) bc[i][0] = 1;
        for (j=0; j<= 3; j++) bc[j][j] = 1;
        for (i=1; i<=MAXN-1; i++)
            for (j=1; j<3; j++)
                bc[i][j] = bc[i-1][j-1] + bc[i-1][j];

        while (true)
        {
            BigInteger n = input.nextBigInteger();
            if (n.compareTo(BigInteger.ZERO) == 0) break;

            BigInteger prime = BigInteger.ZERO;
            int conta = 0;
            while (prime.compareTo(n) < 0)
            {
                conta++;
                prime = prime.nextProbablePrime();
            }
            long c = bc[conta][2];
            if ((c % 2) != 0)
                System.out.println("no");
            else
                System.out.println("yes");
        }
    }
}