/*************************************************************
 * UVA 10069 - Distinct Subsequences - Programming Challenges
 *
 * Autor: Vinicius J. S. Souza
 * Data: 20/07/2009
 * Tecnicas utilizadas: programacao dinamica + big integers
 *************************************************************/


import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class subsequences
{
    public static void main(String[] args) throws FileNotFoundException, IOException
    {
       BufferedReader input = new BufferedReader(
                new InputStreamReader(System.in));
       int nCasos = Integer.parseInt(input.readLine());
       for (; nCasos > 0; nCasos--)
       {
           String seq = input.readLine();
           String subSeq  = input.readLine();
           System.out.println((getOcorrencias(seq, subSeq)).toString());
       }
    }

    public static BigInteger getOcorrencias(String seq, String subSeq)
    {
        Map<Character, List<Integer>> indexes = getCharIndexes(subSeq);
        BigInteger[] tabela = new BigInteger[subSeq.length()];
        for (int i = 0; i < tabela.length; i++)
            tabela[i] = BigInteger.ZERO;
        for (int i = 0; i < seq.length(); i++)
        {
            List<Integer> listI = indexes.get(seq.charAt(i));
            if (listI == null)
                continue;
            for (int k = listI.size()-1; k >= 0; k--)
            {
                int x = listI.get(k);
                if (x == 0)
                    tabela[0] = tabela[0].add(BigInteger.ONE);
                else
                    tabela[x] = tabela[x].add(tabela[x-1]);
            }
        }
        if (tabela.length == 0)
            return BigInteger.ZERO;
        return tabela[subSeq.length()-1];
    }

    public static Map<Character, List<Integer>> getCharIndexes(String subSeq)
    {
        Map<Character, List<Integer>> indexes = new HashMap<Character, List<Integer>>();
        for (int i = 0; i < subSeq.length(); i++)
        {
            List<Integer> list = indexes.get(subSeq.charAt(i));
            if (list == null)
                list = new ArrayList<Integer>();
            list.add(i);
            indexes.put(subSeq.charAt(i), list);
        }
        return indexes;
    }
}
