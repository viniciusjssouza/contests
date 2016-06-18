/***********************************************************************
 * UVa Problem 706 - LCD Display - Programming Challenges
 * Autor: Vinicius J. S. Souza
 * Data: 18/01/2008 
 ***********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

#define NUM_SIZE  15

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);		
	bool inicio = true;
	while (true)
	{
		char num[NUM_SIZE];
		int size = 0;
		scanf("%d %s", &size, num);
		if (!size && !atol(num)) return 0;

		// primeira linha
		for (int i = 0; i < strlen(num); i++)
		{
			putchar(' ');
			for (int k = 0; k < size; k++)
			{
				if (num[i] != '4' && num[i] != '1')
					putchar('-');
				else
					putchar(' ');
			}
			if ((i + 1) < strlen(num))
			{
				putchar(' ');
				putchar(' ');
			}
		}
		putchar(' ');
		putchar('\n');
				
		// proximas 'size' linhas...ate o centro do caractere
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < strlen(num); k++)
			{
				if (num[k] != '1' && num[k] != '2' && num[k] != '3'&& num[k] != '7')
					putchar('|');
				else putchar(' ');
				
				for (int m=0; m < size; m++)
				{
					putchar(' ');
				}
				if (num[k] != '5' && num[k] != '6')
					putchar('|');
				else putchar(' ');
				if ((k+1) < strlen(num)) putchar(' ');
			}
			putchar('\n');
		}
		// linha central --
		for (int i = 0; i < strlen(num); i++)
		{
			putchar(' ');
			for (int k = 0; k < size; k++)
			{
				if (num[i] != '0' && num[i] != '1' && num[i] != '7')
					putchar('-');
				else
					putchar(' ');
			}
			if ((i + 1) < strlen(num))
			{
				putchar(' ');putchar(' ');
			}
		}
		putchar(' ');
		putchar('\n');
		// linhas verticais inferiores
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < strlen(num); k++)
			{
				if (num[k] != '1' && num[k] != '4' && num[k] != '3' && num[k] != '5'
					&& num[k] != '7' && num[k] != '9')
					putchar('|');
				else putchar(' ');
				
				for (int m=0; m < size; m++)
				{
					putchar(' ');
				}
				if (num[k] != '2')
					putchar('|');
				else putchar(' ');
				if ((k+1) < strlen(num)) putchar(' ');
			}
			putchar('\n');
		}
		// linhas horizontais inferiores
		for (int i = 0; i < strlen(num); i++)
		{
			putchar(' ');
			for (int k = 0; k < size; k++)
			{
				if (num[i] != '4' && num[i] != '1' && num[i] != '7')
					putchar('-');
				else
					putchar(' ');
			}
			if ((i + 1) < strlen(num))
			{
				putchar(' ');putchar(' ');
			}
		}
		putchar(' ');
		putchar('\n');
		putchar('\n');
	}	
}