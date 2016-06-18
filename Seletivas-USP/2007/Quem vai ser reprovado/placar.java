/********************************************************************
* Seletiva IME-USP - Quem vai ser reprovado
*
* Autor: Vinicius J. S. Souza
* Data: 05/01/2010
* Tecnicas: ordenacao composta
***********************************************************************/


import java.util.*;
import java.io.*;

public class placar
{
   static class Aluno implements Comparable<Aluno>
   {
      String nome;
      int nota;
    
      public Aluno(String n, int nota)
      {
	 nome = n;
	 this.nota = nota;
      }

      public int compareTo(Aluno a)
      {
	 if (this.nota > a.nota)
	    return -1;
	 if (this.nota < a.nota)
	    return 1;
	 return (this.nome.compareTo(a.nome));
      }
   }

   public static void main(String args[]) throws Exception
   {
      BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
      int instancia = 1;
      while (true)
      {
	 String line = input.readLine();
	 if (line == null || line.equals("")) 
	    break;
	 int N = Integer.parseInt(line);
	 Aluno[] alunos = new Aluno[N];
	 for (int i = 0; i <  N; i++)
	 {
	    StringTokenizer t =  new StringTokenizer(input.readLine());
	    alunos[i] = new Aluno(t.nextToken(), Integer.parseInt(t.nextToken()));
	 }
	 Arrays.sort(alunos);
	 System.out.printf("Instancia %d\n", instancia++);
	 System.out.println(alunos[alunos.length-1].nome + "\n");
      }
   }
}
 
