/***********************************************************************
* Copa do Mundo - Regional - Maratona 2006
*
* Autor: Vinicius J. S. Souza
* Data: 18/03/2010
* Tecnicas: ad-hoc... Matematica simples
* Dificuldade(1-10): 3
*********************************************************************/
#include<iostream>
#include<cstdio>

using namespace std;

int T, N;

int main() {
	while (true) {
		scanf("%d %d", &T, &N);
		if (!T) break;
		char str[50];
		int pontosJogados = N*3;
		int pontosObtidos = 0;
		for (int i = 0; i < T; i++) {		
			int x;
			scanf("%s %d", str, &x);
			pontosObtidos+= x;			
		}
		printf("%d\n", pontosJogados - pontosObtidos);
	}	
	return 0;
}

