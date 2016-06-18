import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.util.Scanner;



public class reverse
{
    public static void main(String args[])
    {
        Scanner input = new Scanner(System.in);
        //Scanner input = new Scanner(new File("in.txt"));

        int nTest = input.nextInt();
        for (int t = 0; t < nTest; t++)
        {
            BigInteger num = input.nextBigInteger();
            num = num.abs();
            String reverse = "";
            //System.out.println(num.toString());
            int iterations = 0;
            reverse = reverseString(num.toString());

            do
            {
                BigInteger num2 = new BigInteger(reverse);
                num = num.add(num2);
                iterations++;
               // System.out.println(num.toString() + " " + num2.toString());
                reverse = reverseString(num.toString());
            }while(!num.toString().equals(reverse));
            
            System.out.println(iterations + " " + reverse);
        }
    }

    public static String reverseString(String str)
    {
        String reverse = "";
        for (int i = 0; i < str.length(); i++)
            reverse = str.charAt(i) + reverse;
        return reverse;
    }
}
