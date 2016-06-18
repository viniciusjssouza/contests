/****************************************************************
* UVa 10130 - Supersale
*
* Autor: Vinicius J. S. Souza
* Data: 02/04/2010
* Tecnicas: DP, 0-1 knapsack
* Dificuldade(1-10): 4 
*****************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int T, N, G, MW;
int Vi[1000], Wi[1000];
int C[1000][1000];

int main() {
	scanf("%d", &T);
	for (int tcase = 0; tcase < T; tcase++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &Vi[i], &Wi[i]);
		} 
		scanf("%d", &G);
		int total = 0;
		for (int k = 0; k < G; k++) {
			scanf("%d", &MW);
			for (int i=0;i<=N ;i++) C[i][0] = 0;
			for (int w=0;w<=MW;w++) C[0][w] = 0;
			for (int i=1;i<=N;i++) {
				  for (int w=1;w<=MW;w++) {
					 if (Wi[i] > w)
						C[i][w] = C[i-1][w];
					 else
						C[i][w] = max(C[i-1][w] , C[i-1][w-Wi[i]]+Vi[i]);
				  }
			}
			total += C[N][MW];
		}
		printf("%d\n", total);
	}
}
