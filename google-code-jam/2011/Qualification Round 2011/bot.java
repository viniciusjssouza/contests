import java.util.*;
import java.io.*;

public class bot {
	
	static int[][] dO = new int[110][2];
	static int[][] dB = new int[110][2];
	static boolean debug = false;
	
	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.valueOf(in.readLine());
		for (int t = 1; t <= T; t++) {
			int opos = 0;
			int bpos = 0;
			String[] line = in.readLine().split("\\s");
			int N = Integer.valueOf(line[0]);
			for (int i = 1; i < line.length; i+= 2) {
				char robo = line[i].charAt(0);
				if (robo == 'O') {
					dO[opos][0] = (i-1)/2;
					dO[opos][1] = Integer.valueOf(line[i+1]);
					opos++;
				} else {
					dB[bpos][0] = (i-1)/2;
					dB[bpos][1] = Integer.valueOf(line[i+1]);
					bpos++;
				}
				dO[opos][0] = dB[bpos][0] = Integer.MAX_VALUE;				
			}
	
			if (debug) {
				for (int i = 0; i < opos || i < bpos; i++) {
					if (i < opos) {
						System.out.print("O: " + dO[i][1] + "  ");
					}
					if (i < bpos) {
						System.out.print("B: " + dB[i][1]);
					}
					System.out.println();
				}
			}
						
			int total = 0;
			int obutton = 1, bbutton = 1;
			for (int o = 0, b = 0; o < opos || b < bpos; ) {
				int otime = Math.abs(dO[o][1]-obutton)+1;
				int btime = Math.abs(dB[b][1]-bbutton)+1;
				if (dO[o][0] < dB[b][0]) {
					// orange's time
					obutton = dO[o][1];
					total += otime;
					if (btime < otime) {
						bbutton = dB[b][1];
					} else {
						if (bbutton < dB[b][1]) {
							bbutton += otime;
							if (bbutton > dB[b][1])
								bbutton = dB[b][1];							
						} else {
							bbutton -= otime;
							if (bbutton < dB[b][1])
								bbutton = dB[b][1];
						}
					}
					o++;
				} else {
					// black's time
					bbutton = dB[b][1];
					total += btime;
					if (otime < btime) {
						obutton = dO[o][1];
					} else {
						if (obutton < dO[o][1]) {
							obutton += btime;
							if (obutton > dO[o][1])
								obutton = dO[o][1];
						} else {
							obutton -= btime;
							if (obutton < dO[o][1])
								obutton = dO[o][1];
						}
					}
					b++;
				}
				if (debug) {
					System.out.printf("Black: %d Orange: %d\n", bbutton, obutton);
					System.out.println("Total: " + total);
				}
			}
			System.out.printf("Case #%d: %d\n", t, total);		
			
			if (debug) {
				System.out.println("---------------");
			}
		}
	}
}