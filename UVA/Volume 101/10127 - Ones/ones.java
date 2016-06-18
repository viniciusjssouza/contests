import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class ones
{
    public static void main(String args[]) throws Exception
    {
        //BufferedReader input = new BufferedReader(new FileReader(new File("in.txt")));
        //BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        Scanner input = new Scanner(System.in);
        while (input.hasNextBigInteger())
        {
            //String str = input.readLine();
            //if (str == null || str.equals("")) break;
            BigInteger n = input.nextBigInteger();
            String str = n.toString();
            int nDigitos =  str.length();
            String min = "";
            for (int i = 0; i < nDigitos; i++)
                min += "1";
            BigInteger div = new BigInteger(min);
            if (div.compareTo(n) < 0)
                div = div.multiply(BigInteger.TEN).add(BigInteger.ONE);
            while (!div.mod(n).equals(BigInteger.ZERO))
            {
               div = div.multiply(BigInteger.TEN).add(BigInteger.ONE);
              // System.out.println(div.toString());
            }
            System.out.println(div.toString().length());
        }
    }
}
