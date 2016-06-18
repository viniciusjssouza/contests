/*
* UVA - 10051 - Tower of Cubes - Programming Challenges
* Tecnicas: DP - LIS aplicada nas cores dos cubos.
* Autor: Vinicius J. S. Souza
* Data: 19/08/2009
*/
#include<iostream>
#include<deque>
#include<string>
#include<vector>

using namespace std;

typedef pair<int, int> Pii;
typedef vector<vector<int> > VVi;
typedef vector<vector<Pii> > VVP;

char fStr[6][10] = {"front", "back", "left", "right", "top", "bottom"};
int indices[6] = {1, 0, 3, 2, 5, 4};

int main()
{
	int n, caso = 1;
	bool isInit = true;
	while (true)
	{
		scanf("%d", &n);
		if (!n) 
			break;
		if (!isInit)
			putchar('\n');
		else
			isInit = false;
		vector< VVi > cubos(n, VVi(101, vector<int>()) );
		VVi input(n, vector<int>(6) );		
		VVi dp(n, vector<int>(6, 1) );
		VVP path(n, vector<Pii>(6) ); 
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < 6; k++)
			{
				scanf("%d", &input[i][k]);
				cubos[i][input[i][k]].push_back(k);
			}
		}
		printf("Case #%d\n", caso);
		if (n==1)
		{
			printf("1\n");
			printf("1 front\n");
			caso++;
			continue; 
		}
/* 
		printf("---- input ----\n");
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < 6; k++)
				printf("%d ", input[i][k]);
			putchar('\n'); 
		}
		printf("\n---- cubos ----\n");
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < 11; k++)
			{
				printf("(");
				for (int m = 0; m < cubos[i][k].size(); m++)
					printf("%d,", cubos[i][k][m]);
				printf(") ");			
			}
			putchar('\n'); 
		}
*/
		int max = 0, ff, initCubo;
		for (int i = n-2; i >= 0; i--)
		{
			for (int k = 0; k < 6; k++)
			{
				int cor = input[i][k];
				for (int m = i+1; m < n; m++)
				{
					for (int p = 0; p < cubos[m][cor].size(); p++)
					{
						int pos = cubos[m][cor][p];
						if (dp[m][pos] + 1 > dp[i][indices[k]])
						{
							dp[i][indices[k]] = dp[m][pos] + 1;
							path[i][indices[k]] = Pii(m, pos);
							if (dp[i][indices[k]] > max)
							{
								max = dp[i][indices[k]];
								ff = indices[k];
								initCubo = i;
							}
						}
					}
				}
			} 	
		}
/*
		printf("\n---- path ----\n");
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < 6; k++)2 back
3 front
			{
				printf("(%d, %d)", path[i][k].first, path[i][k].second);
			}
			putchar('\n'); 
		}
*/
		printf("%d\n", max);
		Pii par(initCubo, ff);
		for (int i = 0; i < max; i++)
		{
			printf("%d %s\n", par.first+1, fStr[par.second]);			 
			par = path[par.first][par.second];
		}
		caso++;
	}	
	return 0;
}
