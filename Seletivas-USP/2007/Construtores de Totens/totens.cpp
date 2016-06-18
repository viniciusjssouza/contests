/***************************************************************
* Construtores de Totens - Seletiva IME USP 2007
* 
* Autor: Vinicius J. S. Souza
* Data: 06/05/2010
* Tecnicas: algoritmo kmp. Compressao de dados na base binaria
***************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define UNDER '_'
#define PIPE '|'

using namespace std;

typedef unsigned long long int64;

int64 toten[1010][1010], pattern[70];
char aux[1010];
int n, M, total;
int t[1010];

void preKmp() {
	t[0] = -1;
	int i = 0;
	for (int j = 1; j < M; j++) {
		if (pattern[j] == pattern[i]) {
			t[j] = t[i];
		} else {
			t[j] = i;
			do {
				i = t[i];
			} while (i>=0 && pattern[j] != pattern[i]);
		}
		i++;
	}
	t[M] = i;
}


int KMP(int col) {
    /* Preprocessing */
	int found = 0;
    preKmp();
	int i = 0;
	for (int j = 0; j < n; j++) {
		while (i >= 0 && toten[j][col] != pattern[i]) 
			i = t[i];
		i++;
		if (i == M) {
			printf("%d %d\n", (j+1-M), col);
			i = t[M];
			found++;
		}
	}  
	return found;
}

int main() {
	int tcase = 1;
	while (!feof(stdin) && scanf("%d %d", &n, &M) == 2) {
		total = n-M+1;
		char c;
		getchar();
		for (int i = 0; i < n; i++) {
			int64 repr = 0;
			gets(aux);
			int auxCount = 0;
			for (int k = 0; k < total; k++) {
				if (!k) {
					for (int j = 0; j < M; j++) {
						if (aux[auxCount++] == PIPE) {
							repr |= (1llu << j);
						}
					}
				} else {
					repr = repr >> 1;
					if (aux[auxCount++] == PIPE)
						repr |= (1llu << (M-1));
				}	
				toten[i][k] = repr;
			}									
		}
		for (int i = 0; i < M; i++) {
			int64 repr = 0;
			gets(aux);
			for (int k = 0; k < M ;k++) {
				if (aux[k] == PIPE) {
					repr |= ((int64)(1llu << k));
				}	
			}
			pattern[i] = repr;
		}
		printf("Instancia %d\n", tcase++);
		int found = -1;
		for (int i = 0; i < total; i++)
		{
			found += KMP(i);
		}
		if (found < 0)
			printf("nenhuma ocorrencia\n");
		putchar('\n');
	}
}

