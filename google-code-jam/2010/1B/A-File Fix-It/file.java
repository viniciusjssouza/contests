/***************************************************************************
* File Fix It - Google Code Jam 2010 - Round 1B 
*
* Autor: Vinicius J. S. Souza
* Data: 19/08/2010
* Tecnicas: ad-hoc
* Dificuldade(1-10): 3
*****************************************************************************/

import java.io.*;
import java.util.*;

public class file {
    
    public static void main(String args[]) throws IOException{
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(input.readLine());
        for (int tcase = 1; tcase <= T; tcase++) {
            String[] line = input.readLine().split("\\s");
            int N = Integer.parseInt(line[0]);
            int M = Integer.parseInt(line[1]);
            TreeSet<String> paths = new TreeSet<String>();
			paths.add("/");
			int conta = 0;
            for (int i = 0; i < N; i++) {
                StringBuffer buffer = new StringBuffer("");
                line = input.readLine().split("/");
				for (int k = 1; k < line.length; k++) {
                    buffer.append("/" + line[k]);
                    paths.add(buffer.toString());
                }
            }
            for (int i = 0; i < M; i++) {
                line = input.readLine().split("/");
				StringBuffer buffer = new StringBuffer();
                for (int k = 1; k < line.length; k++) {
                    buffer.append("/"+line[k]);
                    if (paths.contains(buffer.toString()) == false) {
                        paths.add(buffer.toString());
                        conta++;
                    }
                }
            }
            System.out.printf("Case #%d: %d\n", tcase, conta);
        }
    }
}
