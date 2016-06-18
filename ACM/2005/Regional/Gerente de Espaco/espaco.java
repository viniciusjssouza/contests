/*****************************************************************************
* Gerente de Espaco - ACM - Maratona Regional - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 16/02/2010
* Tecnicas: estrutura de dados - muuuito trabalhoso
* Dificuldade (1-10): 7 
**************************************************************************/
import java.io.*;
import java.util.*;

public class espaco {
	static final boolean DEBUG = false;
	static int N;
	static long D;
	static long id = 0;
	static Block disco=  new Block(-1, "disco", Integer.MAX_VALUE, null, null);
	static NavigableSet<Block> freeSet = new TreeSet<Block>();
	static Map<String, Block> fileToBlock = new HashMap<String, Block>();
	static long freeTotal = 0;
 
	public static void main(String... args) throws Exception {
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
		disco.previous = null;
		while (true) {
			N = Integer.parseInt(input.readLine());
			if (N == 0)
				break;
			id = 0;
			D = parseSize(input.readLine());
			freeTotal = D;
			Block init = new Block(id++, null, D, null, disco);
			disco.next = init;
			freeSet.add(init);
			boolean fullDisc = false;
			for (int i = 0; i < N; i++) {
				if (DEBUG) {
					System.out.println("-------------- Disco apos " + (i) + " -------------------");
					printDisco();
					System.out.println("-----------------\nFreeSet: " + freeSet + "\n-------------------\n");
					System.out.println("FreeTotal = " + freeTotal);
				}
				String[] tokens = input.readLine().split("\\s");
				if (fullDisc)
					continue;
				char command = tokens[0].charAt(0);
				if (command == 'i')
				{
					Block b = new Block(id++, tokens[1], parseSize(tokens[2]), null, null);
					if (b.size > freeTotal) {
						fullDisc= true;
						continue;
					}
					Block where = freeSet.ceiling(new Block(-1, null, b.size, null, null));
					if (where != null) {
						insertBlock(b, where);
					}else {
						optimize();
						insertBlock(b, freeSet.iterator().next());
					}
				} else if (command == 'r') {
					removeBlock(fileToBlock.get(tokens[1]));
				} else if (command == 'o') {
					optimize();
				}
			}
			if (fullDisc)
				System.out.println("ERRO: disco cheio");
			else {
				if (DEBUG) {
					System.out.println("Ao final:");
					printDisco();
					System.out.println("-----------------\nFreeSet: " + freeSet + "\n-------------------\n");
					System.out.println("FreeTotal = " + freeTotal);
				}
				long step = D / 8;
				Block b = disco.next;
				long sobraFree=0, sobraUsed = 0;
				for (long i = 0; i < D; i+= step) {
					long free = 0, used = 0;
					if (sobraFree > step) {
						free = step;
						sobraFree -= step;
					} else {
						free = sobraFree;
						sobraFree = 0;
					}
					if (sobraUsed > step) {
						used = step;
						sobraUsed -= step;
					} else {
						used = sobraUsed;
						sobraUsed = 0;
					}
					for (; b != null && (free+used) < step; b = b.next) {
						if (b.isEmpty()) {
							if (free+used+b.size > step) {
								long add = step - free - used;
								free += add;
								sobraFree += (b.size - add);
							} else {
								free += b.size;
								sobraFree = 0;
							}
						} else {
							if (free+used+b.size > step) {
								long add = step - free - used;
								used += add;
								sobraUsed += (b.size - add);
							} else {
								used += b.size;
								sobraUsed = 0;
							}					
						}
					}
					double p = (double)(free * 100) /  (double)step;
					//System.out.println("\n" + free + "   " + used + "  SobraFree: " + sobraFree + "  SobraUsed:" + sobraUsed);
					if (p > 75.0)
						System.out.print("[ ]");
					else if (p <= 25.0)
						System.out.print("[#]");
					else
						System.out.print("[-]");				
				} 
				System.out.println(); 
			}
			disco.next = null;
			freeSet.clear();
			fileToBlock.clear();
		}
	}
	
	static void removeBlock(Block b) {
		if (b == null || b.isEmpty()) return;
		fileToBlock.put(b.name, null);
		b.name = null;
		freeTotal += b.size;
		if (b.next != null) {
			Block c = b.next;
			if (c.isEmpty()) {
				b.size += c.size;
				freeSet.remove(c);				
				b.next = c.next;
				if (b.next != null) 
					b.next.previous = b;
				c.next = c.previous = null;
			}
		}
		if (b.previous != null) {		
			Block a = b.previous;
			if (a.isEmpty())
			{
				b.size += a.size;
				freeSet.remove(a);
				b.previous = a.previous;
				if (b.previous != null)
					b.previous.next = b;
				a.previous = a.next = null;
			}
		}
		b.id = id++;
		freeSet.add(b);						
	}

	static void optimize() {
		Block ant = disco, next = null;
		for (Block b = disco.next; b != null; b = next) {
			if (b.isEmpty()) {
				if (b.previous != null)
					b.previous.next = b.next;
				if (b.next != null)
					b.next.previous = b.previous;	
				next = b.next;
				b.next = b.previous= null;
			} else {
				ant = b;
				next = b.next;
			}
		}
		Block free = new Block(id++, null, freeTotal, null, ant);
		if (ant != null)
			ant.next = free;
		freeSet.clear();
		freeSet.add(free);
	}

	static void insertBlock(Block toInsert, Block where) {
		Block aux = disco.next;
		while (true) {
			if (aux.isEmpty() && aux.size == where.size)
				break;
			aux = aux.next;
		}
		where = aux;
		freeSet.remove(where);
		if (toInsert.size == where.size) {
			toInsert.next = where.next;
			toInsert.previous = where.previous;
			if (toInsert.next != null)
				toInsert.next.previous = toInsert;
			if (toInsert.previous != null)
				toInsert.previous.next = toInsert;
			where.previous = where.next = null;
		} else {
			where.size -= toInsert.size;
			where.id = id++;
			toInsert.next = where;
			if (where.previous != null)
				where.previous.next = toInsert;
			toInsert.previous=  where.previous;
			where.previous = toInsert;
			freeSet.add(where);
		}
		fileToBlock.put(toInsert.name, toInsert);
		freeTotal -= toInsert.size;
	}

	static long parseSize(String s) {
		long n = Integer.parseInt(s.substring(0, s.length()-2));
		long fator = 1;
		char c = s.charAt(s.length()-2);
		if (c == 'M')
			fator = 1024;
		else if (c == 'G')
			fator = 1048576;
		return (n * fator);
	}

	static void printDisco(){
		for (Block b = disco.next; b != null; b = b.next)
			System.out.println(b);
	}

	static class Block implements Comparable<Block>	{
		String name;
		long size;
		long id;
		Block next = null;
		Block previous = null;

		Block(long id, String name, long size, Block next, Block prev){ 
			this.next = next;
			this.previous = prev;
			this.id = id;
			this.name = name;
			this.size = size;
		}
		
		@Override
		public boolean equals(Object o) {
			return (this.id == ((Block)o).id);
		}		

		public int hashCode() {
			return (int)this.id;
		}		
		
		public int compareTo(Block o) {
			if (o == null) return 1;
			long temp = this.size - o.size;
			if (temp > 0) return 1;
			if (temp < 0) return -1;
			temp = (this.id - o.id);
			if (temp > 0) return 1;
			if (temp < 0) return -1;
			return 0;
		}
		public String toString() {
			return "Id: " + id + "   Name: " + name + "  Size:" + size ; 
		}
		boolean isEmpty() {
			return (name == null || name.length() == 0);
		}
	}
}
