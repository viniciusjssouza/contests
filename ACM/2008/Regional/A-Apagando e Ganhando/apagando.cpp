/********************************************************************
* ACM - 2008 - Eliminatoria Regional - Apagando e Ganhando
*
* Autor: Vinicius J. S. Souza
* Data: 28/07/2009
* Tecnicas utilizadas: programacao dinamica
* Atencao!!! Apenas um algoritmo de ordem n resolve este problema!!!
**********************************************************************/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

char input[100010];
bool used[100010];
char output[100010];

int main()
{
	int d, n;
	while (true)
	{
		scanf("%d %d", &n, &d);
		if (!n && !d) 
			break;
		int size = n-d;
		scanf("%s", input);
		int index = 0;		
		int ptr = 1;
		output[0] = input[0];
		for (int i = 1; i < n; i++, ptr++)
		{
			if (input[i] > input[index] && (d-ptr) >= 0)
			{
				d -= ptr;
				ptr = 0;
				output[ptr] = input[i];
				index = i;				
			}			
			else if (input[i] > input[i-1] && d)
			{
				ptr--;
				output[ptr] = input[i];				
				d--;
				while (output[ptr] > output[ptr-1] && d)
				{
					output[ptr-1] = output[ptr];				
					ptr--;
					d--;
				}
			}
			else output[ptr] = input[i];
			output[ptr+1] = '\0';
			//printf("Output: %s   ptr:%d    d:%d\n", output, ptr, d);
		}	
		for (int i = 0; i < size; i++)
			putchar(output[i]);
		putchar('\n');
/*		char max = 0;
		int index = 0;
		for (int i = 1; i < n && d; i++)
		{
			bool changed = false;
			used[i] = true;
			if (input[i] > '0')
			{
				for (int k = i-1; k >= index && d; k--)
				{
					if (input[i] > input[k] && used[k])
					{
						d--;
						used[k] = false;
						changed = true;						
					}
				}
				if (input[i] >= max)
				{
					max = input[i];
					index = i;
				}
			}
			if (!changed && d >= (n-i))
				used[i] = false;
		}
		for (int i = 0; i < n; i++)
			if (used[i])
				putchar(input[i]);
		putchar('\n');			
*/
	}
	return 0;
}
