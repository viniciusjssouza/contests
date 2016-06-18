/*************************************************************************
* UVA 10094 - Place the Guards
*
* Autor: Vinicius J. S. Souza
* Data: 30/01/2010
* Tecnicas: Reconhecimento de padroes ciclicos
* Padrao: N = 6k +2 ou N = 6k + 3 ?
*************************************************************************/
import java.util.*;
import java.io.*;

public class Main
{
	static int N;  
	static int[] result = new int[1010];

	public static void main(String... args) throws Exception
	{
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
		
		while (true)
		{
			String line = input.readLine();
			if (line == null || line.equals(""))
				break;
			N = Integer.parseInt(line);
			if (N <= 3)
			{
				System.out.println("Impossible");
				continue;
			}
			if (N > 7 && ( ((N-2) % 6) == 0 || ((N-3) % 6) == 0) )
			{
				int k = (N-2) / 6;
				if ( ((N-3) % 6) == 0)
					k = ((N-3) / 6);
				int idx = 0;
				for (int i = 2*k+2; i <= N && idx < N; i+=2, idx++)
					result[idx] = i;
				for (int i =2; i <= 2*k && idx < N; i += 2, idx++)
					result[idx] = i;
				boolean isValid = false;
				int init = -1;
		loop:	do
				{
					init+=2;
					int pos = idx;
					for (int i = init; pos < N && i <= N; pos++, i+=2)
					{
						if (conflict(pos, i))
							continue loop;
						result[pos] = i;
					} 
					for (int i = 1; pos < N && i <= N; pos++, i+=2)
					{
						if (conflict(pos, i))
							continue loop;
						result[pos] = i;
					}
					isValid = true;
				}while(isValid == false);
				
			}
			else
			{
				int idx = 0;
				for (int i = 2; i <= N && idx < N; i+=2, idx++)
					result[idx] = i;
				for (int i = 1; i <= N && idx < N; i+=2, idx++)
					result[idx] = i;
			}
			for (int i = 0; i < N; i++)
				System.out.print(i == 0 ? result[i] : " " + result[i]); 
			System.out.println();			
		}		
	}
	static boolean conflict(int pos, int n)
	{
		for (int i = 0; i < pos; i++)
		{
			if ( (pos - i) == Math.abs(n - result[i]))
				return true;
		}
		return false;
	}
}
