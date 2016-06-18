/*************************************************************
* A - ACM - North America - East Central - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 20/08/2010
* Tecnicas: backtracking.
************************************************************/
import java.util.*;
import java.io.*;

public class acm {
	public static final String end=  "LAST CASE";
	static String[] ss = null;
    static int soma = 0;
    static ArrayList<String> words = new ArrayList<String>();
    static Map<String, Integer> memo = new HashMap<String, Integer>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			int N = Integer.parseInt(in.readLine());
			if (N == 0)
				break;
			HashSet<String> invalid = new HashSet<String>();
			for (int i = 0; i < N; i++) {
				invalid.add(in.readLine());				
			}                        
			while(true) {
				String line = in.readLine();
				if (line.equals(end)) 
					break;
                words.clear();
				ss = line.split("\\s");
                String abr = ss[0].toLowerCase();
				for (int i = 1; i < ss.length; i++) {
					if (invalid.contains(ss[i]) == false)
						words.add(ss[i].toLowerCase());
				}
                 
                int limit = abr.length() - words.size() + 1;
                soma = 0;
                for (int i = limit; i > 0; i--) {
                    String s = abr.substring(0, i);

                    int val = getCombinations(s, words.get(0),0,0);
					if (val > 0)
                    	solve(abr, 1, i, val);
                }
                if (soma == 0)
                    System.out.printf("%s is not a valid abbreviation\n",ss[0]);
                else
                    System.out.printf("%s can be formed in %d ways\n",ss[0], soma);
			}
		}
	}

	static void solve(String abr, int wIdx, int abrCol, int ant) {
        if (wIdx >= words.size()) {
            soma += ant;
            return;
        }
        int mWords = words.size() - wIdx - 1;
        int mAbr = abr.length() - abrCol;
        int limit = mAbr - mWords + abrCol;
        for (int i = limit; i > abrCol; i--) {
            String s = abr.substring(abrCol, i);
            int val = getCombinations(s, words.get(wIdx), 0 , 0);
            if (val > 0) {
                solve(abr, wIdx+1, i, ant*val);
            }
            if (wIdx == words.size()-1)
                break;
        }
	}
            
    static int getCombinations(String menor, String maior, int menorCol, int maiorCol) {
        if (maiorCol >= maior.length() && menorCol < menor.length())
            return 0;
        if (menorCol >= menor.length()) {
            return 1;
        }
        int limit = (maior.length()-maiorCol) - (menor.length()-menorCol) + 1 + maiorCol ;
        int conta = 0;
        for (int i = maiorCol; i < limit; i++) {
            if (maior.charAt(i) == menor.charAt(menorCol)) {
                conta += getCombinations(menor, maior, menorCol+1, i+1);
            }
        }
        return conta;
    }

} 
