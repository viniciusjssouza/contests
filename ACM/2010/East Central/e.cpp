/****************************************************************
* ACM 2010 - East Central USA - E - Polar Bear
*
* Autor: Vinicius J. S. Souza
* Data: 27/10/2011
* Tecnicas: Grids
***************************************************************/
#include<iostream>
#include<cstdio>
#include<deque>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

#define para(i,B,N) for(int i = B; i < N; i++)
#define debug false
//#define trace(x...) 	if(debug)printf(x);


using namespace std;

int R, C, G, K;
bool alive[101][101][2];
bool curr = false;

int countAliveNeighbors(int r, int c) {
	int conta = 0;
	int opp = (c+C/2)%C;
	// counting clockwise
	// N
	if (alive[r == 0 ? r : r-1][r == 0 ? opp : c][curr]) {
			conta++; 
	}
	// NE
	if (alive[r==0 ? r : r-1][r == 0 ? (opp==0 ? C-1 : opp-1) : (c==0 ? C-1 : c-1)][curr]) {
			conta++;
	}
	// E
	if (alive[r][c == 0 ? C-1 : c-1][curr]) {
		conta++;
	}
	// SE
	if (alive[r==R-1 ? r : r+1][r == R-1 ? (opp==0 ? C-1 : opp-1) : (c==0 ? C-1 : c-1)][curr]) {
			conta++;
	}
	// S
	if (alive[r==R-1 ? r : r+1][r == R-1 ? opp : c][curr]) {
			conta++; 
	}
	// SW
	if (alive[r==R-1 ? r : r+1][r == R-1 ? (opp==C-1 ? 0 : opp+1) : (c==C-1 ? 0 : c+1)][curr]) {
			conta++;
	}
	// W
	if (alive[r][(c+1)%C][curr]) {
		conta++;
	}
	// NW
	if (alive[r==0 ? r : r-1][r == 0 ? (opp==C-1 ? 0 : opp+1) : (c==C-1 ? 0 : c+1)][curr]) {
			conta++;
	}
	return conta;
}

void solve() {
	para(g, 0, G) {
		if (debug) printf("Geracao %d\n", g+1);
		para(r,0,R) {
			para(c,0,C) {
				int neighbors = countAliveNeighbors(r,c);
				if (alive[r][c][curr]) {
					if (neighbors < 2 || neighbors > 3) {
						alive[r][c][!curr] = false;
					} else {
						alive[r][c][!curr] = true;
					}
				} else if (!alive[r][c][curr]) {
					if (neighbors == 3) {
						alive[r][c][!curr] = true;
					} else {
						alive[r][c][!curr] = false;
					}
				}
				if (debug)printf("(%d n=%d) ", alive[r][c][!curr], neighbors);
			}
			if (debug) printf("\n");
		}
		curr = !curr;
	}
}

int main()
{
	int ncase = 1;
	while (1) {
		scanf("%d %d", &R, &C);
		if (!R && !C)
			break;
		scanf("%d", &K);
		int r,c;
		memset(alive, false, sizeof(alive)); 
		para(i,0,K) {
			scanf("%d %d", &r, &c);
			alive[r][c][curr] = true;
		}	
		scanf("%d", &G);
		if (debug) printf("-------------------\n");
		solve();
		int conta = 0;
		int r1=-1,c1=-1, r2=-1,c2=-1;
		para(r,0,R) {
			para(c,0,C) {
				if (alive[r][c][curr]) {
					conta++;
					if (r1 < 0) {
						r1 = r;
						c1 = c;
					}
					r2 = r;
					c2 = c;
				}
			}
		}
		printf("Case %d: %d %d %d %d %d\n", ncase++, conta, r1, c1, r2, c2);		
	}
	return 0;
}
