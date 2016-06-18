/*******************************************************************
* Torres de Telefonia Celular - Regional da Maratona de 2009
*
* Autor: Vinicius J. S. Souza
* Data: 13/05/2010
* Tecnicas: geometria computacional - Mininum enclosing circle
*******************************************************************/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<vector>
#include<cstdio>

#define MAXN 45

#define all(v) (v).begin(), (v).end()

#define _inline(f...) f() __attribute__((always_inline)); f

using namespace std;

#define INF 0x7FFFFFFF
#define all(v) (v).begin(), (v).end()

const float EPS = 1e-7;
_inline (int cmp) (float x, float y = 0, float tol = EPS){
   return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
   float x, y;
   point(float x = 0, float y = 0): x(x), y(y) {}
   point operator +(point q) { return point(x + q.x, y + q.y); }
   point operator -(point q) { return point(x - q.x, y - q.y); }
   point operator *(float t) { return point(x * t, y * t); }
   point operator /(float t) { return point(x / t, y / t); }
   /*produto interno */
   float operator *(point q) { return x * q.x + y * q.y; }
   /* produto vetorial */
   float operator %(point q) { return x * q.y - y * q.x; }
   int cmp(point q) const {
   if (int t = ::cmp(x, q.x)) return t;
   return ::cmp(y, q.y);
   }
   bool operator ==(point q) const { return cmp(q) == 0; }
   bool operator !=(point q) const { return cmp(q) != 0; }
   bool operator < (point q) const { return cmp(q) < 0; }
};
float abs(point p) { return hypot(p.x, p.y); }
float arg(point p) { return atan2(p.y, p.x); }                                        

typedef pair<point, float> circle;
                                                              
_inline( bool in_circle)(circle &C, point &p){
	return cmp(abs(p - C.first), C.second) <= 0;
}

point circumcenter(point &p, point &q, point &r) 
{
	point a = p - r, b = q - r, c = point(a * (p + r) / 2.0, b * (q + r) / 2.0);
 	return point(c % point(a.y, b.y), point(a.x, b.x) % c) / (a % b);
}

_inline( circle spanning_circle)(vector<point>& T) 
{
	int n = T.size();
	circle C(point(), -INF);
	for (register int i = 0; i < n; i++) {
		if (!in_circle(C, T[i])){
			C = circle(T[i], 0);
			for (register int j = 0; j < i; j++)	{
				if (!in_circle(C, T[j])){
		 			C = circle((T[i] + T[j]) / 2.0, abs(T[i] - T[j]) / 2.0);
					for (register int k = 0; k < j; k++) {
						if (!in_circle(C, T[k])) {
							point o = circumcenter(T[i], T[j], T[k]);
		 					C = circle(o, abs(o - T[k]));
						}
					}
				}
			}	
		}	
	}
	return C;
}

int N;
vector<point> R(MAXN);
vector<point> aux2(2);
vector<point> aux3(3);
circle circ1, circ2;
float minr = INF;

int main()
{	
	while (true) {
		scanf("%d", &N);
		if (!N) break;
		for (register int i = 0; i < N; i++) {
			scanf("%f %f", &R[i].x, &R[i].y);		
		}
		minr = INF;
		for (register int i = 0; i < N;i++) {
			for (register int k = i+1; k < N; k++) {
				circ1 = circle((R[i] + R[k]) / 2.0, abs(R[i] - R[k]) / 2.0);
				if (cmp(circ1.second, minr) < 0) {
					vector<point> out;
					for (int w = 0; w < N; w++) {
						if (!in_circle(circ1, R[w]))
							out.push_back(R[w]);
					}
					circ2 = spanning_circle(out);
					float radius = circ1.second;
					if (cmp(circ1.second, circ2.second) < 0)
						radius = circ2.second;
					if (cmp(radius, minr) < 0)
						minr = radius;				
				}
				for (register int m = k+1; m< N; m++) {
						point o = circumcenter(R[i], R[k], R[m]);
						circ1 = circle(o, abs(o - R[k]));
						if (cmp(circ1.second, minr) < 0) {
							vector<point> out;
							for (int w = 0; w < N; w++) {
								if (!in_circle(circ1, R[w]))
									out.push_back(R[w]);
							}
							circ2 = spanning_circle(out);
							float radius = circ1.second;
							if (cmp(circ1.second, circ2.second) < 0)
								radius = circ2.second;
							if (cmp(radius, minr) < 0)
								minr = radius;
						}				
				}
			}
		}
		printf("%.2f\n", minr);
	}
	return 0;
}
