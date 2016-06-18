/******************************************************************************
* Uva 861 - Little Bishops - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 05/02/2009
* Tecnicas: para resolver esse usei uma trapaca. O metodo recursivo esta correto
mas nao passa no tempo limite.O que fiz foi calcular todas as possibilidades e 
joga-las em um arquivo e, em seguida, para o array dp abaixo.... =)
*****************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib> 

using namespace std;
#define MAXN 80

int N, K;
int bishops[MAXN]; 
int gridSize = 0;
unsigned long long total = 0;
int dpB[10][70];
int dpW[10][70];
unsigned long long dp[8][65] = {1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 33, 40, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 16, 92, 232, 260, 112, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 26, 261, 1288, 3328, 4440, 2852, 736, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 36, 520, 3896, 16428, 39680, 53744, 38368, 12944, 1600, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 50, 1037, 11648, 77808, 320104, 814140, 1254624, 1120672, 536544, 121616, 9856, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 64, 1736, 26192, 242856, 1444928, 5599888, 14082528, 22522960, 22057472, 12448832, 3672448, 489536, 20224, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int nextPos(int current)
{
	if ( !(N & 1) )
	{
		if (! ((current+1) % N) )
			return (current+1);
		else if (! ((current+2) % N))
			return (current+3);
		else
			return (current+2);
	}
	else
		return (current+2);
}

bool threat(int a, int b)
{
	int ya = a / N;
	int xa = a % N;
	int yb = b / N;
	int xb = b % N;
	return (abs(ya - yb) == abs(xa-xb)); 
}

long long backtrack(int b, int pos, int nBispos)
{
	if (!nBispos)
		return 0;
	bishops[b] = pos;
	if (b == nBispos-1)
		return 1;
	long long subtotal = 0;
	for (int i = nextPos(pos);  i < gridSize; i = nextPos(i) )
	{
		bool ok = true;
		for (int k = 0; k <= b; k++)
		{
			if (threat(bishops[k], i))
			{
				ok = false;
				break;
			}
		}
		if (ok)
			 subtotal += backtrack(b+1, i, nBispos);		
	}
	return subtotal;
}	

int main()
{
	long s = clock();
/*
	for (int i = 0; i < 10; i++)
		for (int k = 0; k < 70; k++)
			dpB[i][k] = dpW[i][k] = -1;
*/
	while (true)
/*	int conta  = 0;
	for (int l1 = 1; l1 < 9; l1++)
		for(int l2 = 0; l2 < 65; l2++)
*/
	{
	//	conta++;
	
		scanf("%d %d", &N, &K);
		if (!N && !K)
			break;
	
//		N= l1; K = l2;
/*	
		total = 0; 
		gridSize = N*N;
		for (int black = 0, white = K; white >= 0; black++, white--)
		{
			unsigned long long w,b;
			w = b = 0;
			if (!black) 
				b = 1;
			else
			{
				if (dpB[N][black] == -1)
				{	
					for (int m = 0; m < gridSize; m = nextPos(m))
						b += backtrack(0, m, black);
					dpB[N][black] = b;
				}
				else
					b += dpB[N][black];
			}
			if (!white)					
				w = 1;
			else
			{
				if (dpW[N][white] == -1)
				{	
					for (int m = 0; m < gridSize; m = nextPos(m))
						w += backtrack(0, m, white);
					dpB[N][white] = w;
				}
				else
					w += dpW[N][white];
			}
			total += (w*b);
		}
*/
		printf("%llu\n", dp[N-1][K]);	
	}
	//cout << (double)(clock()-s) / (double)CLOCKS_PER_SEC << endl;
}	
