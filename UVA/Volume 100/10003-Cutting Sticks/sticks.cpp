/******************************************************************************
* UVa 10003 - Cutting Sticks - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 25/10/2009
* Tecnicas utilizadas: dp com memoization
******************************************************************************/
#include<iostream>
#include<vector>

#define MAX 987654321

using namespace std;

int minimo = MAX;
int SIZE, N;

int backtrack(int cuts[], int** memory, int inf, int sup)
{	
	if (memory[inf][sup] < MAX)
		return memory[inf][sup];
	if (sup - inf == 1)
		return memory[inf][sup] = 0;

	for (int i = inf+1; i < sup; i++)
	{
		int	a = backtrack(cuts, memory, inf, i);
		int b = backtrack(cuts, memory, i, sup);
		int result = a + b + (cuts[sup] - cuts[inf]);
		if (result < memory[inf][sup])
				memory[inf][sup] = result;				
	}	
	return memory[inf][sup];
}

int main()
{
	while (true)
	{
		minimo = MAX;
		scanf("%d", &SIZE);
		if (!SIZE) break;
		scanf("%d", &N);
		int cuts[N+2];
		cuts[0] = 0;
		for (int i = 1; i <= N; i++)
			scanf("%d", &cuts[i]);
		cuts[N+1] = SIZE;
		int** memory = new int*[N+2];
		for (int i = 0; i < N+2; i++)
			memory[i] = new int[N+2];
		for (int i = 0; i < N+2; i++)
			for (int k = i+1; k < N+2; k++)
				memory[i][k] = MAX;
		printf("The minimum cutting is %d.\n", backtrack(cuts, memory, 0, N+1));
	}
	return 0;
}
