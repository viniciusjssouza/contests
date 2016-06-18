/*******************************************************************
* ACM - East-Central Regional Contest - USA - Plaque Pack
*
* Autor: Vinicius J. S. Souza
* Data: 09/08/2010
* Tecnicas: uso de grids, simulacao
* Complexidade: ~ O(N*W^2) 
****************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define MAXN 100
#define BOXN 2*MAXN+5

int N, W, B, H;
char box[2*MAXN+5][15];
char plaque[MAXN][15];

int main() {
	while(true) {
		scanf("%d %d %d", &N, &W, &B);
		if (!N && !W && !B)
			break;
		int htotal = 0;
		memset(box, '.', sizeof(box));
		for (int n = 0; n < N; n++) {
			scanf("%d", &H);
			memset(plaque, '.', sizeof(plaque));
			for (int i = H; i > 0; i--) {
				if (n == 0) 
					scanf("%s", box[BOXN-i]);
				else 
					scanf("%s", plaque[MAXN-i]); 
			}
			if (n > 0) {
				int nivel = 1;
				bool end = false;
				while (!end && nivel <= H) {
					for (int i = nivel; i >= 1 && !end; i--) {
						for (int k = 0; k < W && !end; k++) {
							if (plaque[MAXN+i-nivel-1][k] == 'X' && box[BOXN-htotal+i-1][k] == 'X')
								end = true;
						}						
					}
					if (end) 
						nivel--;
					else nivel++;
				}
				if (htotal + (H-nivel) > B) {
					printf("%d ", htotal);
					memset(box, '.', sizeof(box));
					for (int i = H; i > 0; i--) 
						for (int k = 0; k < W; k++) 
							box[BOXN-i][k] = plaque[MAXN-i][k];
					htotal = H;						
				} else {
					for (int i = 1; i <= H; i++) {
						for (int k = 0; k < W; k++)
							if (plaque[MAXN-i][k] == 'X')
								box[BOXN-htotal+nivel-i][k] = plaque[MAXN-i][k];							
					}
					htotal += (H-nivel);					
				}				
			} else
				htotal += H;							
		}
		printf("%d\n", htotal);
	}	
} 
