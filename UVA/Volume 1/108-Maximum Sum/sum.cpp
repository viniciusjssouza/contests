#include<iostream>
#include<vector>

using namespace std;

int n;

int getSomaMax(vector<vector<int> > &input)
{
	int somas[n+1][n+1][n][n];
	int max =-1000000000;
	for (int h = 1; h <= n; h++)
	{
		for (int l = 1; l <= n; l++)
		{
			//printf("\nSoma: h = %d l = %d\n", h, l);
			for (int i = 0; (i+h) <= n; i++)
			{
				for (int k = 0; (k+l) <= n; k++)
				{
					if (l == 1 && h == 1)
						somas[h][l][i][k] = input[i][k];
					else if (l == 1)
						somas[h][l][i][k] = somas[h-1][1][i][k] + somas[1][1][i+h-1][k];
					else
						somas[h][l][i][k] = somas[h][l-1][i][k] + somas[h][1][i][k+l-1];
					if (somas[h][l][i][k] > max)
						max = somas[h][l][i][k];				
					//printf("Para linha = %d col = %d, soma = %d \n", i, k, somas[h][l][i][k]);				
				}
			}
		}
	}
	return max;
}

int main()
{
	while (!feof(stdin) && scanf("%d", &n) == 1)
	{
		vector<vector<int> > input(n, vector<int>(n, 0));
		for (int i = 0; i < n; i++)
		{
			for (int k = 0 ;k < n; k++)
				scanf("%d", &input[i][k]);
		}
/*
		for (int i = 0; i < n; i++)
		{		
			for (int k =0; k < n; k++)
				printf("%d ", input[i][k]);
			putchar('\n');
		}
*/
		printf("%d\n", getSomaMax(input));
	}	
	return 0;
}
