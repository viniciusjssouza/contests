/************************************************************************
* C - Livro Caixa - ACM - Regional brasileira 2010
*
* Autor: Vinicius J. S. Souza
* Data: 28/09/2010
* Tecnicas: programacao dinamica -> backtracking + memoization
* Dificuldade (1-10): 7
**********************************************************************/
#include<iostream>
#include<algorithm>

#define OK 1
#define NO -1
#define OFFSET 16010

using namespace std;

int N, F;
typedef pair<int,int> pii;

int fluxos[45];
int soma[45];
char result[45]; 
int memo[42][33000];
bool ok;

bool backtrack(int nivel, int total) {
	if (nivel == N) {
		return (total == 0);
	}	
	if (memo[nivel][total+OFFSET] != 0)
		return (memo[nivel][total+OFFSET] == OK);
	// pode ser positivo?
	bool ok = false;
	int next = total - fluxos[nivel];
	if (abs(next) <= soma[nivel+1]) {
		if (backtrack(nivel+1, next)) {
			if (result[nivel] == '-' || result[nivel] == '?')
				result[nivel] = '?';
			else
				result[nivel] = '+';
			ok = true;
		}
	}
	next = total + fluxos[nivel];
	if (abs(next) <= soma[nivel+1]) {
		if (backtrack(nivel+1, next)) {
			if (result[nivel] == '+' || result[nivel] == '?')
				result[nivel] = '?';
			else
				result[nivel] = '-';
			ok = true;
		}
	}
	memo[nivel][total+OFFSET] = (ok ? OK : NO);
	return (ok);
}

int main() {
	while (true) {
		scanf("%d %d", &N, &F);
		if (!N && !F)
			break;
		memset(fluxos, 0, sizeof(fluxos));
		memset(memo, 0, sizeof(memo));
		for (int i = 0; i < N; i++) {
			scanf("%d", &fluxos[i]);
			result[i] = '*';
		}
		soma[N-1] = fluxos[N-1]; 		
		soma[N] = 0;
		for (int i = N-1; i >= 0; i--) {
			soma[i] = soma[i+1] + fluxos[i];
		}
		if (!backtrack(0, F))
			printf("*\n");
		else {
			result[N] = '\0';
			printf("%s", result);
			putchar('\n');
		}
	}
	return 0;
} 
