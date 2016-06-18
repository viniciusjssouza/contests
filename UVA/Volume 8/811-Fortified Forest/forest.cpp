/**********************************************************************
* UVa 811 - Fortified Forest
*
* Autor: Vinicius J. S. Souza
* Data: 24/12/2009
* Tecnicas: backtracking (busca completa) + convex hull
***********************************************************************/
#include<iostream>
#include<deque>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

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

////////////////////////////////////////////////////////////////////////////////
// Comparação radial.
//
bool radial_lt(point p, point q) 
{
   point P = p - point::pivot, Q = q - point::pivot;
   double R = P % Q;
   if (cmp(R)) return R > 0;
   return cmp(P * P, Q * Q) < 0;
}

////////////////////////////////////////////////////////////////////////////////
// Determina o fecho convexo de um conjunto de pontos no plano.
//
// Destrói a lista de pontos T.
//
polygon convexHull(vector<point>& T) 
{
   int j = 0, k, n = T.size(); polygon U(n);
   point::pivot = *min_element(all(T));
   sort(all(T), radial_lt);
   for (k = n-2; k >= 0 && ccw(T[0], T[n-1], T[k]) == 0; k--);
   reverse((k+1) + all(T));
   for (int i = 0; i < n; i++) {
   // troque o >= por > para manter pontos colineares
   while (j > 1 && ccw(U[j-1], U[j-2], T[i]) >= 0) j--;
   U[j++] = T[i];
   }
   U.erase(j + all(U));
   return U;
}

int N;
int minV, nTrees;
double extraWood;
vector<int> cut;

struct Tree
{
   int value;
   int length;
   point pos;
};

double euclidianDist(point &a, point &b)
{
   return sqrt((double)pow((a.x-b.x), 2.0) + (double)pow((a.y-b.y), 2.0));
}

double calculFence(polygon &p)
{
   int s = p.size();
   double total = 0.0;
   for (int i = 1; i < s; i++)
      total += (euclidianDist(p[i], p[i-1]));
   total += euclidianDist(p[s-1], p[0]);
   return total;
}

void backtrack(vector<Tree> &forest, deque<int> &subset, vector<bool> &in, int current)
{
   subset.push_back(current);
   in[current] = true;

   for (int i = current+1; i < N; i++)
      backtrack(forest, subset, in, i);
   /*   
   printf("Subset: ");
   for (int i = 0; i < subset.size(); i++)
	printf("%d ", subset[i]+1);
 */
   int totalL = 0, totalV = 0, totalTrees = N - subset.size();
   for (int i = 0; i < N; i++)
      if (!in[i])
      {
	 totalL += forest[i].length;
	 totalV += forest[i].value;
      }
   
   //printf("  Value:%d  Length:%d ", totalV, totalL);
   if ( (totalV < minV) || (totalV == minV && totalTrees < nTrees) )
   {
      vector<point> points;
      int s = subset.size();
      for (int i = 0; i < s; i++)
	 points.push_back(forest[subset[i]].pos);
      polygon fence = convexHull(points);
      double fenceLength = calculFence(fence);
      //printf("  fence:%lf ", fenceLength);
      double aux = ((double)totalL) - fenceLength;
      if (cmp(aux) >= 0)
      {
	 minV = totalV;
	 nTrees = totalTrees;
	 cut.clear();
	 for (int i = 0; i < N; i++)
	    if (!in[i])
	       cut.push_back(i+1);
	  extraWood = aux;
      }
   } 
   //putchar('\n');
   in[current] = false;
   subset.pop_back();
}

int main()
{
   int id=1;
   while (true)
   {
      minV = nTrees = INF;
      scanf("%d", &N);
      if (!N) 
	 break;
      if (id > 1) putchar('\n');
      vector<Tree> forest(N);
      for (int i = 0; i < N; i++)
	 scanf("%lf %lf %d %d", &forest[i].pos.x, &forest[i].pos.y, &forest[i].value, &forest[i].length);
      /* subset de arvores que NAO serao cortadas */
      deque<int> subset;
      vector<bool> in(N, false);
      for (int i = 0; i < N; i++)
	 backtrack(forest, subset, in, i);
      printf("Forest %d\n", id);
      printf("Cut these trees: ");
      for (int i = 0; i < cut.size(); i++)
      {
	 if (i) putchar(' ');
	 printf("%d", cut[i]);
      }
      printf("\nExtra wood: %.2lf\n", extraWood);
      cut.clear();      
      id++;
   }
   return 0;
}
 
 
