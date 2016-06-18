/************************************************************************
* Amigos ou Inimigos - Regional - Maratona 2006 
*
* Autor: Vinicius J. S. Souza
* Data: 23/03/2010
* Tecnicas: geometria basica.
* Dificuldade(1-10): 4
*************************************************************************/
#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

#define SIZE 270

const int fator = SIZE / 2;

int consultas[1010][2];
int lado[SIZE*SIZE][2];

int N, a, b, K, max;

inline bool inLine(int x, int y) {
	return (y == (a*x+b));
}

void updateGrid(int x, int y, int &c) {
	x -= fator;
	y = fator-y;
	if (!inLine(x,y)) {
		lado[c][0] = x;
		lado[c++][1] = y;
	//	cout << "Update " << (x) << " " << (y) << " = " << grid[y][x]<< endl;	
	}
}

int main() {
	//long s = clock();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int mx = 0;
		scanf("%d %d", &a, &b);
		scanf("%d", &K);
		for (int k = 0; k < K; k++) {
			scanf("%d %d", &consultas[k][0], &consultas[k][1]);
			if (consultas[k][0] > mx)
				mx = consultas[k][0];
			if (consultas[k][1] > mx)
				mx = consultas[k][1];
		}
		int x = fator;
		int y = fator;
		int xmax= x, xmin = x, ymax = y, ymin = y;
		int c = 0;
		updateGrid(x, y, c);
		x--; 
		while(c <= mx) {
		   for(; x >= xmin && c <= mx; x--) {
				updateGrid(x,y,c);
			}
			xmin = x;
			for(; y >= ymin && c <= mx; y--) {
				updateGrid(x,y,c);
			}
			ymin = y;
			for(; x <= xmax && c <= mx; x++) {
				updateGrid(x,y,c);
			}
			xmax = x;
			for(; y <= ymax && c <= mx; y++) {
				updateGrid(x,y,c);
			}
			ymax = y;
		}
		printf("Caso %d\n", i+1);
		for (int k =0; k < K; k++) {
			int x1 = lado[consultas[k][0]][0];
			int y1 = lado[consultas[k][0]][1];
			int x2 = lado[consultas[k][1]][0];
			int y2 = lado[consultas[k][1]][1];
			bool lado1 = (y1 < (a*x1+b));
			bool lado2 = (y2 < (a*x2+b));
			if (lado1 == lado2) 
				printf("Mesmo lado da fronteira\n");
			else
				printf("Lados opostos da fronteira\n"); 
		}
/*
		for (int m = 0; m <= mx; m++) {
			printf("%d -> (%d %d)\n", m, lado[m][0], lado[m][1]);
		}
*/
	}	
	//cout << (double)(clock()-s)  / (double)CLOCKS_PER_SEC << endl;
	return 0;
}
