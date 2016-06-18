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
int maxX, maxY, minX, minY;

void insertQueue(map<int, map<int,int> > &castle, polygon &poly,  map<int, bool> &segX, map<int,bool> &segY, point next, point nextHalf, point &current, deque<point> &fila)
{
   if (!castle[(int)next.x+MAXV][(int)next.y+MAXV])
   {
      if ( (segX[next.x] || segY[next.y]) &&      
	  (in_poly(next, poly) == OUTSIDE || in_poly(nextHalf, poly) == OUTSIDE))
	    return;
      //cout << "Entrei para (" << next.x << ", " << next.y << ")\n";	  
      fila.push_back(next);
      castle[(int)next.x+MAXV][(int)next.y+MAXV] = castle[(int)current.x+MAXV][(int)current.y+MAXV] + 1;      
   }
}

int bfs(polygon &poly, map<int, bool> &segX, map<int,bool> &segY)
{
   deque<point> fila;
   fila.push_front(entrance);
   map<int, map<int,int> > castle; 

   while (!fila.empty())
   {
      point current = fila.front();
      fila.pop_front();
      if (current.x == treasure.x && current.y == treasure.y)
	 return castle[(int)current.x+MAXV][(int)current.y+MAXV];
      insertQueue(castle, poly, segX, segY, point(current.x+1, current.y), point(current.x+0.5, current.y), current, fila);
      insertQueue(castle, poly, segX, segY, point(current.x, current.y-1), point(current.x, current.y-0.5), current, fila);
      insertQueue(castle, poly, segX, segY, point(current.x-1, current.y), point(current.x-0.5, current.y), current, fila);
      insertQueue(castle, poly, segX, segY, point(current.x, current.y+1), point(current.x, current.y-0.5), current, fila); 
   }
}

int main()
{
   long st = clock();
   int id = 0;
   while(true)
   {
      int N;
      id++;
      maxX = maxY = -INF;
      minX = minY = +INF;
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
	 maxX = max(maxX, (int)poly[i].x);
	 minX = min(minX, (int)poly[i].x);
	 maxY = max(maxY, (int)poly[i].y);
	 minY = min(minY, (int)poly[i].y);
      }
      scanf("%lf %lf", &entrance.x, &entrance.y);
      maxX = max(maxX, (int)entrance.x);
      minX = min(minX, (int)entrance.x);
      maxY = max(maxY, (int)entrance.y);
      minY = min(minY, (int)entrance.y);
      scanf("%lf %lf", &treasure.x, &treasure.y);
      maxX = max(maxX, (int)treasure.x);
      minX = min(minX, (int)treasure.x);
      maxY = max(maxY, (int)treasure.y);
      minY = min(minY, (int)treasure.y);
/*  
    cout << inpolygon(poly, point(8.5,2)) << endl;
      cout << inpolygon(poly, point(11,7)) << endl;
      cout << inpolygon(poly, point(1100,5)) << endl;
*/
      printf("Castle %d: %d\n", id, bfs(poly, segX, segY));
   }
   //cout << (double)((double)(clock()-st) / (double)CLOCKS_PER_SEC) << endl;
} 

