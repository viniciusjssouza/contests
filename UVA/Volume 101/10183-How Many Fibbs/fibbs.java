import java.io.FileNotFoundException;
import java.math.*;
import java.util.*;

public class fibbs
{
    static List<BigInteger> list;
    public static void main(String args[]) throws FileNotFoundException
    {
        Scanner input = new Scanner(System.in);
        //Scanner input = new Scanner(new java.io.File("in.txt"));
        list = new ArrayList<BigInteger>();
        BigInteger n1 = BigInteger.ONE;
        BigInteger n2 = new  BigInteger("2");
        BigInteger max = new BigInteger("10000000000" +
                "0000000000" +
                "0000000000" +
                "0000000000" +
                "0000000000" +
                "0000000000" +
                "0000000000" +
                "0000000000" +
                "0000000000" +
                "00000000000000");

        list.add(BigInteger.ZERO);
        list.add(BigInteger.ONE);
        list.add(new BigInteger("2"));
        
        while (list.get(list.size()-1).compareTo(max) <= 0)
        {
            BigInteger _new = list.get(list.size()-1).add(list.get(list.size()-2));
           //if (list.size() < 100) System.out.println(_new.toString());
            list.add(_new);
        }
        //System.out.println(list.size());
        BigInteger a = BigInteger.ONE;
        BigInteger b = BigInteger.ONE;
        while (true)
        {
            a = input.nextBigInteger();
            b = input.nextBigInteger();
            if (a.compareTo(b) > 0)
            {
                System.out.println(0);
                continue;
            }
            if (a.compareTo(BigInteger.ZERO) == 0 &&
                    b.compareTo(BigInteger.ZERO) == 0)
                break;
 //           int res1 = seqSearch(a.subtract(BigInteger.ONE), 0);
//            int res2 = seqSearch(b, res1);
            int res1 = binarySearch(a.subtract(BigInteger.ONE));
            int res2 = binarySearch(b);

            //System.out.println(res2 + " --- " + res1);
            int result = res2 - res1;
            System.out.println(result);
        }
        
    }

    public static int binarySearch(BigInteger n)
    {
        int meio = list.size() / 2;
        int compare = n.compareTo(list.get(meio));
        if (compare < 0)
            return particiona(n, 0, meio);
        else if (compare > 0)
            return particiona(n, meio, list.size());
        else
            return meio;
    }

    public static int particiona(BigInteger n, int begin, int end)
    {
        //System.out.println("Begin:" + begin + "  End:" + end);
        if (end - begin <= 1)
        {
            int compare = n.compareTo(list.get(end));
            if (compare == 0)
                return end;
            else
                return begin;
        }
        int meio = ((begin + end)/ 2);
        int compare = n.compareTo(list.get(meio));
        if (compare < 0)
            return particiona(n, begin, meio);
        else if (compare > 0)
            return particiona(n, meio, end);
        else
            return meio;
    }

    public static int seqSearch(BigInteger n, int begin)
    {
        int i = begin;
        while (list.get(i).compareTo(n) < 0)
            i++;
        if (list.get(i).compareTo(n) == 0 || i == 0)
            return i;
        i--;
        return i;
    }
}