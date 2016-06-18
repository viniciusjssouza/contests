/* UVa 113 - Power of Cryptography
 *
 * Autor: Vinicius J. S. Souza
 * Data: 12/01/2011
 * Tecnicas: Busca binaria
 */

import java.io.*;
import java.util.*;
import java.math.*;

public class power {

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        while (in.ready()) {
            String line = in.readLine();
            if (line.length() == 0)
                break;
            int n = Integer.parseInt(line);
            line = in.readLine();
            BigInteger p = new BigInteger(line);
            BigInteger k = BigInteger.valueOf(500000000l);
            BigInteger sup = BigInteger.valueOf(1000000010l);
            BigInteger inf = BigInteger.valueOf(0);
            while (true) {
                BigInteger res = k.pow(n);
                int cmp = res.compareTo(p);
                if (cmp == 0)
                    break;
                if (cmp > 0) {
                    sup = k;

                } else {
                    inf = k;
                }
                k = sup.add(inf).divide(BigInteger.valueOf(2));
            }
            System.out.println(k.toString());
        }
    }
}