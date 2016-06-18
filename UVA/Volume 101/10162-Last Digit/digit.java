import java.util.*;
import java.io.*;
import java.math.*;


public class digit 
{
   static int CYCLE = 100;
   
   public static void main(String[] args) throws IOException
   {
      //long start = System.currentTimeMillis();
      BigInteger[] memory = new BigInteger[CYCLE];
      BigInteger ten = new BigInteger("10");
      BigInteger hundred = new BigInteger("100");
      memory[0]  = BigInteger.ZERO;
      for (int i = 1; i < CYCLE; i++)
      {
	 BigInteger subtotal = BigInteger.ONE;
	 for (int k = 0; k < i; k++)
	    subtotal = subtotal.multiply(new BigInteger(Integer.toString(i%10)));
	 memory[i] = memory[i-1].add(subtotal).mod(ten);
	 //System.out.println(i + " -> " + (memory[i].mod(ten)));
      }
      BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
      while (true)
      {
          BigInteger N = new BigInteger(input.readLine());
          if (N.equals(BigInteger.ZERO))
              break;
          System.out.println(memory[N.mod(hundred).intValue()]);
      }
      //System.out.println(System.currentTimeMillis() - start);
   }
} 
