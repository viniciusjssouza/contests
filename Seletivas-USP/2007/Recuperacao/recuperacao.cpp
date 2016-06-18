/*******************************************************************
* Recuperacao - Seletivas - IME-USP - 2007
*
* Autor: Vinicius J. S. Souza
* Data: 10/02/2010
* Dificuldade (0-10): 2
******************************************************************/
#include<cstdio>
#include<iostream>

using namespace std;

int a[110];

int main() {
	int N, inst = 1;
	while(!feof(stdin) && scanf("%d", &N) == 1) {
		if (inst > 1)
			putchar('\n');
		for (int i = 0; i< N; i++)
			scanf("%d", &a[i]);
		bool found = false;
		for (int i = 0; i < N; i++) {
			int soma = 0;
			for (int k = 0; k < i; k++) {
				soma += a[k];
			}
			if (soma == a[i])
			{
				found = true;
				printf("Instancia %d\n%d\n", inst++, soma);
				break;
			} 
		}
		if (!found)	
			printf("Instancia %d\nnao achei\n", inst++);
	}
}
