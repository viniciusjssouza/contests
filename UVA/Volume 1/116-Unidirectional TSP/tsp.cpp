/**************************************************************************************
* UVA 116 - Undirectional TSP - Programming Challenges 
* 
* Autor: Vinicius J. S. Souza
* Data: 26/07/2009
* Tecnicas utilizadas: programacao dinamica
***************************************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>

#define MAX 1000000000

using namespace std;

int nLin, nCol;

int data[101][101];
int tabela[101][101];
int parent[101][101];
string order[101][101];

void printPath(int i, int k)
{
	if (k > 0)
		printPath(parent[i][k], k-1);
	printf("%d", i+1);
	if (k != nCol-1)
		putchar(' ');
}

int main()
{	
	while (scanf("%d %d", &nLin, &nCol) == 2)
	{
		for (int i = 0; i < nLin; i++)
			for (int k = 0; k < nCol; k++)
				scanf("%d", &data[i][k]);

		// caso 1 x n
		if (nLin == 1)
		{
			int soma = 0;
			for (int i = 0; i < nCol; i++)
			{
				if (i)
					putchar(' ');
				printf("1");
				soma += data[0][i];				
			}
			printf("\n%d\n", soma);
			continue;
		}
		
	 	// demais casos
		vector<string> rowStr(nLin);
		for (int i = 0; i < nLin; i++)	
		{	
			tabela[i][0] = data[i][0];
			parent[i][0] = -1;
			stringstream buffer;
			buffer << i;
			order[i][0] = rowStr[i] = buffer.str();
		}

		for (int k = 1; k < nCol; k++)
		{
			for (int i = 0; i < nLin; i++)
			{
				int sup = i-1;
				int central = i;
				int inf = i+1;
				
				if (!i)
					sup = nLin-1;
				else if (i == nLin-1)
					inf = 0;
				
				if (tabela[sup][k-1] < tabela[central][k-1])
				{
					tabela[i][k] = tabela[sup][k-1];
					parent[i][k] = sup;
					order[i][k] = order[sup][k-1] + rowStr[i];
				}
				else if (tabela[central][k-1] < tabela[sup][k-1])
				{
					tabela[i][k] = tabela[central][k-1];
					parent[i][k] = central;
					order[i][k] = order[central][k-1] + rowStr[i];
				}
				else
				{
					if (order[sup][k-1] < order[central][k-1])
					{
						tabela[i][k] = tabela[sup][k-1];
						parent[i][k] = sup;
						order[i][k] = order[sup][k-1] + rowStr[i];
					}
					else
					{
						tabela[i][k] = tabela[central][k-1];
						parent[i][k] = central;
						order[i][k] = order[central][k-1] + rowStr[i]; 
					}						
				}										

				if (tabela[inf][k-1] < tabela[i][k])
				{
					tabela[i][k] = tabela[inf][k-1];
					parent[i][k] = inf;
					order[i][k] = order[inf][k-1] + rowStr[i];
				}
				else if (tabela[inf][k-1] == tabela[i][k])
				{
					if (order[inf][k-1] < order[i][k])
					{
						tabela[i][k] = tabela[i][k];
						parent[i][k] = inf;
						order[i][k]  = order[inf][k-1] + rowStr[i];
					}	
				}
				tabela[i][k] += data[i][k];			
			}
		}
		int minPath = MAX, index; 	
		for (int i = 0; i < nLin; i++)
		{
			if (tabela[i][nCol-1] < minPath)
			{
				minPath = tabela[i][nCol-1];
				index = i;
			}
			else if (tabela[i][nCol-1] == minPath)
			{
				if (order[i][nCol-1] < order[index][nCol-1])	
				{
					minPath = tabela[i][nCol-1];
					index = i;
				}
			}
		}
		printPath(index, nCol-1);			
		printf("\n%d\n", minPath);
	}
	return 0;
}

