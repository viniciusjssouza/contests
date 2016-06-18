/*************************************************
 * Fair Warning - Google Code Jam 2010 - Qualification
 *
 * Autor: Vinicius J. S. Souza
 * Data: 23/07/2010
 * Tecnicas: teoria dos numeros: mdc e aritmetica modular. BigInteger
 * Dificuldade (1-10): 7
 */

import java.io.*;
import java.math.*;
import java.util.*;

public class warning {

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int C = Integer.parseInt(in.readLine());
        for (int tcase = 1; tcase <= C; tcase++) {
            String[] line = in.readLine().split("\\s");
            BigInteger[] data = new BigInteger[line.length - 1];
            int menorIdx = 0;
            for (int i = 1; i < line.length; i++) {
                data[i - 1] = new BigInteger(line[i]);
                if (data[i-1].compareTo(data[menorIdx]) < 0)
                    menorIdx = i-1;
            }
            BigInteger temp = data[menorIdx];
            data[menorIdx] = data[0];
            data[0] = temp;
            BigInteger a = data[0];
            BigInteger T = BigInteger.ZERO;
            for (int i = 1; i < data.length; i++) {
                T = data[i].subtract(a).gcd(T);
            }
            //System.out.println(T.toString() + " ... " + new BigInteger("5").modInverse(T));
            System.out.printf("Case #%d: %s\n", tcase, (T.subtract(data[0].mod(T))).mod(T).toString());
        }
    }
}
