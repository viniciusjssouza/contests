/*****************************
* Elastico - Seletiva IOI 2003
*
* Autor: Vinicius J. S. Souza
* Data: 21/07/2010
* Tecnicas: programacao dinamica  + geometria computacional
* Dificuldade: 7
*******************************/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

struct point {
   double x, y;
   point(double x = 0, double y = 0): x(x), y(y) {}
   /* produto vetorial */
   double operator %(point q) { return x * q.y - y * q.x; }
};

int N, dp[205][205];
point pontos[205];

bool fcmp(const point &a, const point &b) {
	float v = atan2(a.y, a.x) - atan2(b.y, b.x);
	return v <= 0;
} 

bool antiHorario(point &base, point &a, point &b) {
	point vetorA = point(a.x - base.x, a.y - base.y);
	point vetorB = point(b.x - base.x, b.y - base.y);
	return (vetorA % vetorB) > 0.0;
}

int main() {
	int tcase = 1;
	while(true) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &pontos[i].x, &pontos[i].y);
		}
		sort(pontos+1, pontos+N+1, fcmp);
		pontos[0].x = pontos[0].y = 0;		
		int maxv = 1;
		for (int i = 1; i <= N; i++) {
			dp[i][0] = 1;
			for (int j = 1; j < i; j++) {
				dp[i][j] = 0;
				for (int k = 0; k < j; k++) {
					if (dp[j][k] > dp[i][j] && antiHorario(pontos[i], pontos[k], pontos[j]))
						dp[i][j] = dp[j][k];
				}
				dp[i][j]++;
				if (dp[i][j] > maxv)
					maxv = dp[i][j];
			}
		}
		printf("Teste %d\n%d\n\n", tcase++, maxv+1);		
	}
	return 0;
} 
