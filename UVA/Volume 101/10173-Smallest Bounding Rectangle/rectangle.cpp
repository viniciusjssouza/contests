/***************************************************************************
* UVA - 10173 - Smallest Bounding Rectangle
*
* Autor: Vinicius J. S. Souza
* Data: 03/02/2010
* Tecnicas: geometria computacional, rotacao de sistemas de coordenadas,
	busca binaria, fecho convexo.
**************************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>

using namespace std;

int N;
double xmax, xmin, ymax, ymin;

#define INF 0x7FFFFFFF
#define all(v) (v).begin(), (v).end()
#define PI 3.141592654
#define SEARCH 11

const double EPS = 1e-10;
const double LIM = 1e-12;

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

double dist(point &a, point &b)
{
   return sqrt((double)pow((a.x-b.x), 2.0) + (double)pow((a.y-b.y), 2.0));
}
void rotate(polygon &original, polygon &rot, double teta)
{
	xmax = ymax = -INF;
	ymin = xmin = INF;
	int size = original.size();
	for (int i = 0; i < size; i++)
	{
		double hip= abs(original[i]);
		double ang = arg(original[i]);
		double alfa = ang - teta;
		rot[i].x = hip * cos(alfa);
		rot[i].y = hip * sin(alfa);
		if (cmp(xmin, rot[i].x) > 0)
			xmin = rot[i].x;
		if (cmp(ymin, rot[i].y) > 0)
			ymin = rot[i].y;
		if (cmp(xmax, rot[i].x) < 0)
			xmax = rot[i].x;
		if (cmp(ymax, rot[i].y) < 0)
			ymax = rot[i].y;
	}
}

double arredonda(double num, int precisao)
{
	double fatorPrecisao = pow(10.0, (double)precisao);
	double x = ( num * fatorPrecisao)+ 0.5;
	x = floor(x);
	return (x / fatorPrecisao);
}

double calculArea()
{
	return ( (ymax - ymin) * (xmax - xmin) );	
}

int main()
{
	while (true)
	{
		scanf("%d", &N);
		if (!N)
			break;
		vector<point> T(N);
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &T[i].x, &T[i].y);
		if (N <= 2)
		{
			printf("0.0000\n");
			continue;
		}
		polygon hull = convexHull(T);
		double inc = PI / 180.0;
		double range = PI / 4.0;
		double begin = 0.0;
		double end = PI / 2.0; 		
		double minArea = INF;
		double middle = PI / 4.0;
		polygon rot(N);
		for (int i = 0; i < 12; i++)
		{			
			for (double teta = begin; cmp(teta, end) <= 0; teta += inc)
			{
				rotate(hull, rot, teta);
				double area = calculArea();
				if (cmp(area, minArea) < 0)
				{
					minArea = area;
					middle = teta;
				}
			} 
			range = 2*inc;
			begin = middle - range;
			end = middle + range; 
			inc /= 10.0;
			
		}		
		printf("%.4lf\n", arredonda(minArea, 4));
	}
	return 0;
}
