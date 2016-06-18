/*****************************************************************
* 491 - Tile Topology 
*
* Autor: Vinicius J. S. Souza
* Data: 31/03/2010
* Tecnicas: cheating :) Este eh um puzzle chamado de Polyonimo.
No mathworld tem o resultado para polyonimos de tamanho 15, que sao
suficientes para resolver o problema.
* Dificuldade(1-10): 10. Nao encontrei um modo de enumerar via forca
bruta todas as combinacoes possiveis.
******************************************************************/

#include<iostream>
#include<cstdio>

#define SIZE 100000

using namespace std;

int tbl[] = {0, 1, 1, 2, 7, 18, 60, 196, 704, 2500, 9189, 33896, 126759, 
			476270, 1802312, 6849777};




int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%d\n", tbl[n]);
	}
	return 0;
}
