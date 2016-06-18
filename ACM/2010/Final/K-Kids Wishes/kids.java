import java.io.*;
import java.util.*;

public class kids {
	static int K, W;
	static Map<Integer, Set<Integer>> grafo;
	static Map<Integer, Boolean> used;
	static Map<Integer, Integer> parent;
	static int count;

	public static void main(String args[]) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			String[] line = in.readLine().split("\\s");
			K = Integer.parseInt(line[0]);
			W = Integer.parseInt(line[1]);
			if (K == 0 && W == 0)
				break;
			grafo = new HashMap<Integer, Set<Integer> >();
			boolean ok = true;
			for (int i = 0; i < W; i++) {
				line = in.readLine().split("\\s");
				int a = Integer.parseInt(line[0]);
				int b = Integer.parseInt(line[1]);
				if( grafo.get(a) == null)
					grafo.put(a, new HashSet<Integer>());
				if( grafo.get(b) == null)
					grafo.put(b, new HashSet<Integer>());
				Set<Integer> setA = grafo.get(a);
				Set<Integer> setB = grafo.get(b);
				setA.add(b);
				setB.add(a);
				if (setA.size() > 2) 
					ok = false;
				if (setB.size() > 2)
					ok = false;				
			}
			used = new HashMap<Integer, Boolean>();
			parent = new HashMap<Integer, Integer>();
			if (ok) {
				for (int k : grafo.keySet()) {
					count = 0;
					if (used.get(k) == null && findCycle(k) && count < K) {
						ok = false;
						break;
					}	
				}
			}
			System.out.printf("%c\n", ok ? 'Y' : 'N');
		}
	}
	
	static boolean findCycle(int v) {
		used.put(v, true);
		count++;
		Set<Integer> e = grafo.get(v); 
		for (int w : e) {
			if (used.get(w) == null) {
				parent.put(w, v);
				if (findCycle(w))
					return true;
			} else {
				Integer p = parent.get(v);
				if (p != null && p != w) {
					return true;
				}
			}	
		} 
		return false;		
	}
}
