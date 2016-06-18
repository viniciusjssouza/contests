/**********************************************************************
* UVa 866 - Intersecting Line Segments
*
* Autor: Vinicius J. S. Souza
* Data: 20/02/2010
* Tecnicas: geometria computacional - interseccao de segmentos ;)
* Dificuldade(1-10): 5 
******************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>

#define INF 0x7FFFFFFF
#define all(v) (v).begin(), (v).end()
#define PI 3.141592654

const double EPS = 1e-10;
inline int cmp(double x, double y = 0, double tol = EPS) 
{
   return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point 
{
   double x, y;
   point(double x = 0, double y = 0): x(x), y(y) {}
   point operator +(point q) { return point(x + q.x, y + q.y); }
   point operator -(point q) { return point(x - q.x, y - q.y); }
   point operator *(double t) { return point(x * t, y * t); }
   point operator /(double t) { return point(x / t, y / t); }
   double operator *(point q) { return x * q.x + y * q.y; }
   double operator %(point q) { return x * q.y - y * q.x; }
   int cmp(point q) const {
   if (int t = ::cmp(x, q.x)) return t;
   return ::cmp(y, q.y);
   }
   bool operator ==(point q) const { return cmp(q) == 0; }
   bool operator !=(point q) const { return cmp(q) != 0; }
   bool operator < (point q) const { return cmp(q) < 0; }
   static point pivot;
};
point point::pivot;
double abs(point p) { return hypot(p.x, p.y); }
double arg(point p) { return atan2(p.y, p.x); }

////////////////////////////////////////////////////////////////////////////////
// Decide se os segmentos fechados pq e rs têm pontos em comum.
//
bool seg_intersect(point p, point q, point r, point s) {
	point A = q - p, B = s - r, C = r - p, D = s - q;
	int a = cmp(A % C) + 2 * cmp(A % D);
    int b = cmp(B % C) + 2 * cmp(B % D);
    if (a == 3 || a == -3 || b == 3 || b == -3) return false;
    if (a || b || p == r || p == s || q == r || q == s) return true;
	int t = (p < r) + (p < s) + (q < r) + (q < s);
    return t != 0 && t != 4;
}

point segs[10000][2];

int main() {
	int cases, N, ptr, total;
	scanf("%d", &cases);
	for (int i = 0; i< cases; i++) {
		ptr = 0;
		if (i)
			putchar('\n');
		scanf("%d", &N);
		total = N;
		for (int k = 0; k < N; k++, ptr++) {
			scanf("%lf %lf %lf %lf", &segs[ptr][0].x, &segs[ptr][0].y, 
							 &segs[ptr][1].x, &segs[ptr][1].y);
		}
		for (int k = 0; k < ptr; k++) {
			for (int m = k+1; m < ptr; m++) {
				if (seg_intersect(segs[k][0], segs[k][1], segs[m][0], segs[m][1]) ) {
					total+=2;
				}
			} 
		}
		printf("%d\n", total);
	}
}

