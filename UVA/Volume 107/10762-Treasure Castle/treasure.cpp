#include<iostream>
#include<vector>
#include<cmath>
#include<deque>
#include<map>
#include<set>

using namespace std;

#define INSIDE	1  
#define OUTSIDE 0
#define BOUNDARY -1

#define MAXV  10000
#define INF 0x7FFFFFFF
#define all(v) (v).begin(), (v).end()

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

typedef vector<point> polygon;

inline int ccw(point p, point q, point r) 
{
   return cmp((p - r) % (q - r));
}

double euclidianDist(point &a, point &b)
{
   return sqrt((double)pow((a.x-b.x), 2.0) + (double)pow((a.y-b.y), 2.0));
}

////////////////////////////////////////////////////////////////////////////////
// Decide se q está sobre o segmento fechado pr.
//
bool between(point p, point q, point r) 
{
   return ccw(p, q, r) == 0 && cmp((p - q) * (r - q)) <= 0;
}

inline double angle(point p, point q, point r) 
{
   point u = p - q, v = r - q;
   return atan2(u % v, u * v);
}

////////////////////////////////////////////////////////////////////////////////
// Classifica o ponto p em relação ao polígono T.
//
// Retorna 0, -1 ou 1 dependendo se p está no exterior, na fronteira
// ou no interior de T, respectivamente.
//
int in_poly(point p, polygon& T) 
{
   double a = 0; int N = T.size();
   for (int i = 0; i < N; i++) 
   {
      if (between(T[i], p, T[(i+1) % N])) return -1;
      a += angle(T[i], p, T[(i+1) % N]);
   }
   return cmp(a) != 0;
}

typedef pair<point, int> pi;
point entrance, treasure;


struct CmpPi
{
   bool operator()(const pi &a, const pi &b)
   {
      return (a.second <= b.second);
   }
};
/* Distancia Mahataniana */
int calculDist(point &p)
{
   return (abs(p.x - treasure.x) + abs(p.y - treasure.y));
}

void insertQueue(map<int, map<int,int> > &castle, polygon &poly,  map<int, bool> &segX, map<int,bool> &segY, point next, point nextHalf, point &current, set<pi, CmpPi> &fila)
{
   if (castle[(int)next.x+MAXV][(int)next.y+MAXV] && castle[(int)next.x+MAXV][(int)next.y+MAXV] <= castle[(int)current.x+MAXV][(int)current.y+MAXV]+1)
      return;
   if ( (segX[next.x] || segY[next.y]) &&      
	  (in_poly(next, poly) == OUTSIDE || in_poly(nextHalf, poly) == OUTSIDE))
	    return;
   fila.insert(pi(next, castle[(int)current.x+MAXV][(int)current.y+MAXV]+1 + calculDist(next) ));
   castle[(int)next.x+MAXV][(int)next.y+MAXV] = castle[(int)current.x+MAXV][(int)current.y+MAXV]+1;
}

int aStar(polygon &poly, map<int, bool> &segX, map<int,bool> &segY)
{
   map<int, map<int,int> > castle; 
   set<pi, CmpPi> fila;
   fila.insert(pi(entrance,calculDist(entrance)));
   castle[(int)entrance.x+MAXV][(int)entrance.y+MAXV] = 0;
   int minimo = INF;
   
   while (!fila.empty())
   {	
      pi par = *fila.begin();
      point current = par.first;
      //printf("Entrei (%lf, %lf)\n", current.x, current.y);
      
      fila.erase(fila.begin());
      if (par.second >= minimo) continue;
      if (current.x == treasure.x && current.y == treasure.y)
      {
	 if (castle[(int)current.x+MAXV][(int)current.y+MAXV] < minimo)
	    minimo = castle[(int)current.x+MAXV][(int)current.y+MAXV];
	 return minimo;
      }
      insertQueue(castle, poly, segX, segY, point(current.x+1, current.y), point(current.x+0.5, current.y), current, fila);
      insertQueue(castle, poly, segX, segY, point(current.x, current.y-1), point(current.x, current.y-0.5), current, fila);
      insertQueue(castle, poly, segX, segY, point(current.x-1, current.y), point(current.x-0.5, current.y), current, fila);
      insertQueue(castle, poly, segX, segY, point(current.x, current.y+1), point(current.x, current.y-0.5), current, fila); 
   }
   return minimo;
}

int main()
{
   long st = clock();
   int id = 0;
   while(true)
   {
      int N;
      id++;
      scanf("%d", &N);
      if (!N) break;
      polygon poly(N);
      map<int, bool> segX;
      map<int, bool> segY;
      for (int i = 0; i < N; i++)
      {
	 scanf("%lf %lf", &poly[i].x, &poly[i].y);
	 segX[poly[i].x] = true;
	 segY[poly[i].y] = true;
      }
      scanf("%lf %lf", &entrance.x, &entrance.y);
      scanf("%lf %lf", &treasure.x, &treasure.y);
      printf("Castle %d: %d\n", id, aStar(poly, segX, segY));
   }
   //cout << (double)((double)(clock()-st) / (double)CLOCKS_PER_SEC) << endl;
} 

 
