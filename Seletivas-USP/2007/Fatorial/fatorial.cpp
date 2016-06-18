/*************************************************************************
* Fatorial - Seletiva IME-USP 2007
*
* Autor: Vinicius J. S. Souza
* Data: 05/04/2010
* Tecnicas: matematica
* Dificuldade(1-10): 4
*************************************************************************/

#include<iostream>
#include<cstdio>

using namespace std;

#define MAXV  1000010
#define FATOR 100000000000llu

typedef unsigned long long int64;

int64 memo[MAXV];
int64 n;

int main() {
    int tcase = 1;
    memo[0] = memo[1] = 1;
    int64 current = 1;
    for (int64 i = 2; i < MAXV; i++) {
	current *= i;
	while (!(current % 10))
	   current /= 10;
	current %= FATOR;
	memo[i] = current % 10;
    }
    while (scanf("%llu", &n) == 1) {
	printf("Instancia %d\n%llu\n\n", tcase++, memo[n]);
    }
    return 0;
}
