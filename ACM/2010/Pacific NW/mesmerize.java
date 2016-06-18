/*********************************************************************
* ICPC - Pacific Northwest 2010 - Mesmerization of the Count
*
* Autor: Vinícius J. S. Souza
* Data: 18/10/2011
* Tecnicas: força bruta + hashing
*************************************************************************/
import java.util.*;
import java.io.*;
import java.awt.*;

public class mesmerize {
	static Map<Long, Integer> mapa = new HashMap<Long, Integer>();
	
	public static void main(String[] args) throws Exception {
		
		long start = System.currentTimeMillis();
		long[] cubos = new long[4010];
		for (long c = 1; c < 4000; c++) {
			long cubo = c*c*c;
			mapa.put(cubo, (int)c);
			cubos[(int)c] = cubo;
		}
		/*for (long l : mapa.keySet()) {
			System.out.println(l + "  " + mapa.get(l) + "  " + mapa.get(l));
		}*/
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));		
		while (true) {
			int N = Integer.valueOf(in.readLine());
			if (N == 0) {
				break;
			}
			boolean ok = false;
			int resa= Integer.MAX_VALUE, resb = 0, resc = 0;
			for (long b = 1; b < 2000 && !ok; b++) {
				long res = cubos[(int)b]*(long)N;
				for (long a = 1; a + 2*b < 4000; a++) {
					long dif = res - cubos[(int)a];
					Integer c = mapa.get(dif);
					if (c != null && a+c+2*b < 4000) {
						resa = (int)Math.max(a,c);
						resb = (int)b;
						resc = (int)Math.min(a, c);
						ok = true;
						break;
					}
				}
			}
			if (!ok)
				System.out.println("No value.");
			else
				System.out.printf("(%d/%d)^3 + (%d/%d)^3 = %d\n", resa,resb,resc,resb,N);
		}
		System.out.println((System.currentTimeMillis() - start) / 1000.0);
	}
}