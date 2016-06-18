/************************************************************
* Last Year at Marienbad - Seletiva IME-USP 2006
*
* Autor: Vinicius J. S. Souza
* Data: 31/03/2010 
* Tecnicas: backtracking
* Dificuldade(1-10): 7
**************************************************************/
#include<iostream>
#include<vector>
#include<map>
#include<cstdio>

using namespace std;

#define OP -1
#define MY 1
#define GANHA 1
#define PERDE 2

typedef vector<int> vi;

map<vi, int> memo; 
vi tab(6);

int backtrack(int jog) {
	int m = memo[tab];
	if (m == GANHA) 
		return jog;
	else if (m == PERDE)
		return -jog;
	bool end = true;
	for (int i = 0; i < 6; i++) {
		for (int k = tab[i]; k > 0; k--) {
			end = false;
			tab[i] -= k;
			int result = backtrack(-jog);
			tab[i] += k;
			if (result == OP) {
				jog == OP ? memo[tab] = GANHA : PERDE;					
				return OP;	
			}
		}
	}
	if (end) {
		memo[tab] = GANHA;					
		return jog;		
	}
	jog == MY ? memo[tab] = GANHA : PERDE;
	return MY;
}

int main() {
	int N;
	scanf("%d", &N);
	for (int tcase = 1; tcase <= N; tcase++) {
		for (int i = 0; i < 6; i++)
			scanf("%d", &tab[i]);			
		int result = OP;
		bool end = true;
		for (int i = 0; i < 6 && result == OP; i++) {
			for (int k = tab[i]; k >0; k--) {
				end = false;
				tab[i] -= k;
				result = backtrack(OP);
				if (result != OP) {
					break;	
				}
				tab[i] += k;
			}
		}
		if (end)
			printf("Instancia %d\n%s\n\n", tcase, "sim");
		else printf("Instancia %d\n%s\n\n", tcase, (result == OP) ? "nao":"sim");
		
	} 
	return 0;
}
