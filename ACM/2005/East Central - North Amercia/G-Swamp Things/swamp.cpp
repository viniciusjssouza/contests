/***************************************************************************
* G-Swamp Things - ACM - East Central - North America 2005  
*
* Autor: Vinicius J. S. Souza
* Data: 04/09/2010
* Tecnicas: forca bruta
* Dificuldade (1-10): 5
*****************************************************************************/
#include<cstdio>
#include<algorithm>

using namespace std;

const double EPS = 1e-10;
inline int cmp(double x, double y = 0, double tol = EPS){
   return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
   double x, y;
   point(double x = 0, double y = 0): x(x), y(y) {}
   int cmp(point q) const {
   		if (int t = ::cmp(x, q.x)) return t;
   		return ::cmp(y, q.y);
   }
   bool operator ==(point q) const { return cmp(q) == 0; }
   bool operator !=(point q) const { return cmp(q) != 0; }
   bool operator < (point q) const { return cmp(q) < 0; }
};

/* Reta by = ax+c */
struct line {
    double a; // coef de x
    double b; // coef de y;
    double c; // termo constante
    line(double a=1.0, double c=1.0, double b = 1.0) {
	this->a =a; this-> c = c; this->b = b;
    }
};

int N;
point pontos[1010];

void point2Line(point &p1, point &p2, line &l) {
    if (!cmp(p1.x, p2.x)) {
	l.a = 1.0; l.b = 0.0;
	l.c = -p1.x;		
    } else {
	l.b = 1.0;
	l.a = -(p1.y - p2.y) / (p1.x-p2.x);
	l.c = -(l.a * p1.x) - (l.b * p1.y);
    }
    l.c = -l.c;
    l.a = -l.a;
}

bool inLine(line &l, point &p) {
	return (!cmp(p.y, l.a*p.x+l.c));		
}

int main() {
	int tcase = 1;
	while (true) {
		scanf("%d", &N);
		if (!N) 
			break;
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf", &pontos[i].x, &pontos[i].y);			
		}
		line l;
		int maior = 0;
		for (int i = 0; i < N; i++) {
			for (int k = i+1; k < N; k++) {
				point2Line(pontos[i], pontos[k], l);
				int conta = 2;
				for (int j = k+1; j < N; j++) {
					if (inLine(l, pontos[j])) {
						conta++;
					}
				}
				maior = max(maior, conta);
			}
		}
		if (maior < 4)
			maior = 0;
		printf("Photo %d: %d points eliminated\n", tcase++, maior);		
	}
	return 0;
}
 

