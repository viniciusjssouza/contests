#include<iostream>
#include<vector>
#include<cmath>
#include<deque>
#include<map>
#include<set>

#define INSIDE	1  
#define OUTSIDE 0
#define BOUNDARY -1
#define INF 0x7FFFFFFF
#define MAXV  10000

using namespace std;

const double EPS = 1e-10;
inline int cmp(double x, double y = 0, double tol = EPS) 
{     return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;  }

struct Point 
{
   double x, y;  
   Point(double x=0.0, double y=0.0):x(x), y(y){}
};
typedef vector<Point> Polygon;
typedef pair<Point, int> pi;
Point entrance, treasure;

/* Produto interno dos vetores AB e BC */
double dot(Point &a, Point &b, Point &c)
{
   Point ab((b.x-a.x), (b.y-a.y));
   Point bc((c.x-b.x), (c.y-b.y));
   return (ab.x * bc.x + ab.y * bc.y);
}

/* Produto vetorial dos vetores AB e AC -> AB x AC */
double cross(Point &a, Point &b, Point &c)
{
   Point ab((b.x-a.x), (b.y-a.y));
   Point ac((c.x-a.x), (c.y-a.y));
   return (ab.x * ac.y - ab.y * ac.x);
}

double euclidianDist(Point &a, Point &b)
{
   return sqrt((double)pow((a.x-b.x), 2.0) + (double)pow((a.y-b.y), 2.0));
}

/* Distancia do ponto p ao segmento formado por AB */
double distPointToSegment(Point &a, Point &b, Point &c)
{
   double dist = cross(a, b, c) / euclidianDist(a, b);
   int dot1 = dot(a,b,c);
   if (dot1 > 0) return euclidianDist(b,c);
   int dot2 = dot(b, a, c);
   if (dot2 > 0) return euclidianDist(a,c);
   return abs(dist);
}

int inPolygon(Polygon &polygon, Point p)
{
   int counter = 0;
   int N = polygon.size();
   double xinters;
   Point p1 = polygon[0];
   for (int i=1; i<=N ;i++) 
   {
      Point p2 = polygon[i % N];
      double dist = distPointToSegment(p1, p2, p);
      if (cmp(dist) == 0)
	 return BOUNDARY;
      if (p.y > min(p1.y,p2.y)) 
      {
	 if (p.y <= max(p1.y,p2.y)) 
	 {
	    if (p.x <= max(p1.x,p2.x)) 
	    {
	       if (p1.y != p2.y) 
	       {
		  xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
		  if (p1.x == p2.x || p.x <= xinters)
		     counter++;
	       }
	    }
	 }
      }
      p1 = p2;
   }
   if (!(counter & 1))
      return(OUTSIDE);
   else
      return(INSIDE);
}

struct CmpPi
{
   bool operator()(const pi &a, const pi &b)
   {
      return (a.second <= b.second);
   }
};
/* Distancia Mahataniana */
int calculDist(Point &p)
{
   return (abs(p.x - treasure.x) + abs(p.y - treasure.y));
}

void insertQueue(map<int, map<int,int> > &castle, Polygon &poly,  map<int, bool> &segX, map<int,bool> &segY, Point next, Point nextHalf, Point &current, set<pi, CmpPi> &fila)
{
   if (castle[(int)next.x+MAXV][(int)next.y+MAXV] && castle[(int)next.x+MAXV][(int)next.y+MAXV] <= castle[(int)current.x+MAXV][(int)current.y+MAXV]+1)
      return;
   if ( (segX[next.x] || segY[next.y]) &&      
	  (inPolygon(poly, next) == OUTSIDE || inPolygon(poly, nextHalf) == OUTSIDE))
	    return;
   fila.insert(pi(next, castle[(int)current.x+MAXV][(int)current.y+MAXV]+1 + calculDist(next) ));
   castle[(int)next.x+MAXV][(int)next.y+MAXV] = castle[(int)current.x+MAXV][(int)current.y+MAXV]+1;
}

int aStar(Polygon &poly, map<int, bool> &segX, map<int,bool> &segY)
{
   map<int, map<int,int> > castle; 
   set<pi, CmpPi> fila;
   fila.insert(pi(entrance,calculDist(entrance)));
   castle[(int)entrance.x+MAXV][(int)entrance.y+MAXV] = 0;
   int minimo = INF;
   
   while (!fila.empty())
   {	
      pi par = *fila.begin();
      Point current = par.first;
      //printf("Entrei (%lf, %lf)\n", current.x, current.y);
      
      fila.erase(fila.begin());
      if (par.second >= minimo) continue;
      if (current.x == treasure.x && current.y == treasure.y)
      {
	 if (castle[(int)current.x+MAXV][(int)current.y+MAXV] < minimo)
	    minimo = castle[(int)current.x+MAXV][(int)current.y+MAXV];
	 return minimo;
      }
      insertQueue(castle, poly, segX, segY, Point(current.x+1, current.y), Point(current.x+0.5, current.y), current, fila);
      insertQueue(castle, poly, segX, segY, Point(current.x, current.y-1), Point(current.x, current.y-0.5), current, fila);
      insertQueue(castle, poly, segX, segY, Point(current.x-1, current.y), Point(current.x-0.5, current.y), current, fila);
      insertQueue(castle, poly, segX, segY, Point(current.x, current.y+1), Point(current.x, current.y-0.5), current, fila); 
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
      Polygon poly(N);
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
   cout << (double)((double)(clock()-st) / (double)CLOCKS_PER_SEC) << endl;
} 

