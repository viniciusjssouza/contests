/****************************************************************
* Seletivas IME-USP - Nao e mais um joguinho Canadense
*
* Autor: Vinicius J. S. Souza
* Data: 05/01/2010
* Tecnicas: o automato pode ser resolvido com recursao. A cada passo
tem-se, no maximo, duas ramificacoe, mas a maioria delas tem-se
apenas uma, possibilitando a recursao.
****************************************************************/


import java.util.*;
import java.io.*;

public class contagem
{
   static class Edge
   {
      char destino;	    
      int valor;
      
      public Edge(char d, int v) 
      {
	 destino = d;
	 valor = v;
      }
   }
   static HashMap<Character, Edge[]> p  = new HashMap<Character, Edge[]>();
   static HashMap<Character, Edge[]> q  = new HashMap<Character, Edge[]>();
   static String word;
   static long total = 0;
   static int wlen = 0;
   static
   {
      Edge[] pa = new Edge[1];
      Edge[] pb = new Edge[2];
      Edge[] qa = new Edge[1];
      Edge[] qb = new Edge[1];
      pb[0] = new Edge('p', 1);
      pa[0] = new Edge('p', 1);
      pb[1] = new Edge('q', 1);
      qb[0] = new Edge('q', 2);
      qa[0] = new Edge('q', 2);
      p.put('a', pa); p.put('b', pb);
      q.put('a',qa); q.put('b', qb);
   }

   public static void main(String args[]) throws Exception
   {
      BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
      int cont = 1;
      while ((word = input.readLine()) != null && word.equals("") == false)
      {
	 wlen = word.length();
	 total = 0;
	 backtrack(0, 'p', 1);
	 System.out.printf("Palavra %d\n", cont++);
	 System.out.println(total + "\n");
      }
   }

   static void backtrack(int nivel, char v, long subtotal)
   {
      if (nivel == wlen)
      {
	 if (v == 'q')
	    total += subtotal;
	 return;
      }
      char c = word.charAt(nivel);
      HashMap<Character, Edge[]> mapa = (v == 'p' ? p : q);
      Edge[] edges = mapa.get(c);
      if (edges == null) return;
      for (Edge e : edges)
      {
	 backtrack(nivel+1, e.destino, subtotal*e.valor);	 
      }
   }
} 
