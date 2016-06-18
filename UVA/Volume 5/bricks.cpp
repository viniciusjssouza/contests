/**************************************************************************
* UVa - 591 - Box of Bricks
* 
* Autor: Vinicius J. S. Souza 
* Data: 04/02/2011
*********************************************************************/
#include<iostream>
#include<cstdio>

using namespace std;

int N, data[51];

int main() {
	int test = 1;
	while (true) {
		if (test > 1)
			putchar('\n');
		scanf("%d", &N);
		if (!N)
			break;
		int soma = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &data[i]);
			soma += data[i];
		}
		int sz = soma / N;
		int moves = 0;
		for (int i = 0; i < N; i++)
			if (data[i] < sz)
				moves += (sz - data[i]);
		printf("Set #%d\n", test++);
		printf("The minimum number of moves is %d.\n", moves);
	}
	return 0;
}