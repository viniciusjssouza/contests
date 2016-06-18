/**********************************************************
* The Snappers - Google Code Jam 2010 - Qualification Round
*
* Autor: Vinicius J. S. Souza
* Data: 21/07/2010
* Algoritmo: simple math - O(1)
* Dificuldade: 3
*********************************************************/

#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

int main() {
	int tcase;
	scanf("%d", &tcase);
	for (int i = 1; i <= tcase; i++) {
		int N, K;
		scanf("%d %d", &N, &K);
		int onState = (1 << N)-1;
		int result = K % (onState+1);
		printf("Case #%d: %s\n", i, result == onState ? "ON" : "OFF"); 
	}
	return 0;
} 

