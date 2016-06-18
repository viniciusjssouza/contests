#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

#define INF 123456789.0

const double EPS = 1e-6f;
inline int cmp(const double &x, const double &y = 0, double tol = EPS) 
{
   return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point 
{
   double x, y;
   int id;
   point(double x = 0, double y = 0): x(x), y(y) {}
   point operator +(const point &q) { return point(x + q.x, y + q.y); }
   point operator -(const point &q) { return point(x - q.x, y - q.y); }
   point operator *(const double &t) { return point(x * t, y * t); }
   point operator /(const double &t) { return point(x / t, y / t); }
   double operator *(const point &q) { return x * q.x + y * q.y; }
   double operator %(const point &q) { return x * q.y - y * q.x; }
   int cmp(point &q) const {
 	  if (int t = ::cmp(x, q.x)) return t;
 	  return ::cmp(y, q.y);
   }
   bool operator ==(point &q) const { return cmp(q) == 0; }
   bool operator !=(point &q) const { return cmp(q) != 0; }
   bool operator < (point &q) const { return cmp(q) < 0; }
};
double abs(const point &p) { return hypot(p.x, p.y); }

int ccw(point &p, point &q, point &r) 
{
   return cmp((p - r) % (q - r));
}


////////////////////////////////////////////////////////////////////////////////
// Decide se os segmentos fechados pq e rs têm pontos em comum.
//
bool seg_intersect(point &A, point &B, point &C, point &D) {
	 return ccw(A,C,D) != ccw(B,C,D) && ccw(A,B,C) != ccw(A,B,D);
}

typedef pair<double, int> pdi;
typedef vector<vector<pdi> > grafo;
struct seg {
	point a, b;
	seg(point &p1, point &p2) {a = p1; b = p2;}
	seg() {}
};

point o,d;
int N;
seg segs[155];
double dist[350];
bool intree[350];
int id;

double solve(grafo &g) {
	for (int i = 0; i < id; i++) {
		dist[i] = INF;
		intree[i] = 0;
	}
	dist[0] = 0.0;
	int v = 0;
	while (!intree[v]) {
		intree[v] = true;
		for (int i = 0;i < g[v].size(); i++) {
			int w = g[v][i].second;
			double peso = g[v][i].first;
			if (cmp(dist[w], dist[v]+peso) > 0) {
				dist[w] = dist[v]+peso;				
			}
		}
		v = 1;
		double d = INF;
		for (int i = 1; i < id; i++) {
			if ( !intree[i] && cmp(d,dist[i]) > 0) {
				d = dist[i];
				v = i;
			} 
		}	
	}
	return dist[1];
}


int main() {
	while (true) {
		scanf("%lf %lf %lf %lf %d", &o.x, &o.y, &d.x, &d.y, &N);
		if (!o.x && !o.y && !d.x && !d.y && !N)
			break;
		o.id = 0;
		d.id = 1;
		id = 2;
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf %lf %lf", &segs[i].a.x, &segs[i].a.y, &segs[i].b.x, &segs[i].b.y);			
			segs[i].a.id = id++;
			segs[i].b.id = id++;
		}
		if (o == d) {
			printf("%.2f\n", 0.0);
			continue;
		}
		bool ok = true;
		for (int i = 0; i < N && ok; i++) {
			if (seg_intersect(o,d, segs[i].a, segs[i].b)) 
				ok = false;
		}
		if (ok) {
			printf("%.2lf\n", abs(d-o));
			continue;
		}
		segs[N].a = o;
		segs[N].b = d;
		grafo g(id);
		for (int i = 0; i <= N; i++) {
			for (int k = i+1; k <= N; k++) {
				bool f1, f2,f3,f4;
				f1 = f2 = f3 = f4 = true;
				for (int m = 0; m < N; m++) {
					if (m == i || m == k)
						continue;
					if (!f1 && !f2 && !f3 && !f4)
						break; 
					if (f1 && seg_intersect(segs[i].a, segs[k].a, segs[m].a, segs[m].b))
						f1 = false;
					if (f2 && seg_intersect(segs[i].a, segs[k].b, segs[m].a, segs[m].b))
						f2 = false;
					if (f3 && seg_intersect(segs[i].b, segs[k].a, segs[m].a, segs[m].b))
						f3 = false;
					if (f4 && seg_intersect(segs[i].b, segs[k].b, segs[m].a, segs[m].b))
						f4 = false;
				}
				if (f1) {
					double d = abs(segs[i].a - segs[k].a);
					g[segs[i].a.id].push_back(pdi(d, segs[k].a.id));
   					g[segs[k].a.id].push_back(pdi(d, segs[i].a.id));
				}
				if (f2) {
					double d = abs(segs[i].a - segs[k].b);
					g[segs[i].a.id].push_back(pdi(d, segs[k].b.id));
   					g[segs[k].b.id].push_back(pdi(d, segs[i].a.id));
				}
				if (f3) {
					double d = abs(segs[i].b - segs[k].a);
					g[segs[i].b.id].push_back(pdi(d, segs[k].a.id));
   					g[segs[k].a.id].push_back(pdi(d, segs[i].b.id));
				} if (f4) {
					double d = abs(segs[i].b - segs[k].b);
					g[segs[i].b.id].push_back(pdi(d, segs[k].b.id));
   					g[segs[k].b.id].push_back(pdi(d, segs[i].b.id));
				}
			} 
		}
		printf("%.2lf\n", solve(g));
	}
	return 0;
}
