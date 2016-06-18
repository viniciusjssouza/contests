/********************************************************************************
* ACM - Escultura a Laser - Regional de 2009
*
* Autor: Vinicius J. S. Souza
* Data: 24/05/2010
* Tecnicas: ad-hoc
* Dificuldade: 5
*******************************************************************************/

import java.io.*;
import java.util.*;

public class laser {

	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			int H, C;
			String[] line = in.readLine().split("\\s");
			H = Integer.parseInt(line[0]);
			C = Integer.parseInt(line[1]);
			if (H == 0 && C == 0)
				break;
			int viz = -1, atual = -1, maxv = -1, minv = 0x3f3f3f3f;
			int conta = 0;
			boolean started = false;
			line = in.readLine().split("\\s");
			for (String str : line) {
				viz = atual;
				atual = Integer.parseInt(str);				
				if (viz == -1) {					
					minv = atual;
				} else {
					if (atual < viz) {
						if (atual >= minv) {
							conta += (viz - atual);
						}else {
							conta += (viz-minv);							
						}						
					} 
					minv = Math.min(minv, atual);						
					
				}
			}
			System.out.printf("%d\n", (conta + (H-minv)));
		}
	}

}


