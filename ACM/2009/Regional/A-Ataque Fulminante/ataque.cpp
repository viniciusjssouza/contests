/****************************************************
* Ataque Fulminante - Maratona - Regional 2009
*
* Autor: Vinicius J. S. Souza
* Data: 09/04/2010
* Tecnicas: geometria computacional
* Dificuldade: 9
*****************************************************/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define PI 3.14159265358979323846

#define NO 0
#define TAN 1
#define SEC 2


const double INF = 100000.0;
const double EPS = 1e-4;
inline int cmp(double x, double y = 0, double tol = EPS) {
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

struct circle {
  point center;
  double r;
  circle() {}
  circle(point c, double raio) {
      r = raio; center = c;
  }
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

void point2Line(point &p, double m, line &l) {
    if (fabs(m) >= INF) {
	l.b = 0.0;
	l.a = 1.0; 
	l.c = -p.x;
    } else {  
      l.a = -m;
      l.b = 1.0;
      l.c = -((l.a*p.x) + (l.b*p.y));
      l.a = -l.a;
      l.c = -l.c;
    }
}

inline double dist(point &a, point &b) {
   return sqrt((double)pow((a.x-b.x), 2.0) + (double)pow((a.y-b.y), 2.0));
}

inline int ccw(point p, point q, point r) {
  return cmp((p - r) % (q - r));
}

inline double angle(point p, point q, point r) {
  point u = p - q, v = r - q;
  return atan2(u % v, u * v);
}

////////////////////////////////////////////////////////////////////////////////
// Decide se q está sobre o segmento fechado pr.
//
bool between(point p, point q, point r) {
  return ccw(p, q, r) == 0 && cmp((p - q) * (r - q)) <= 0;
}

////////////////////////////////////////////////////////////////////////////////
// Classifica o ponto p em relação ao polígono T.
//
// Retorna 0, -1 ou 1 dependendo se p está no exterior, na fronteira
// ou no interior de T, respectivamente.
//
int inPoly(point &p, point &t1, point &t2, point &t3) {
  double a = 0; int N = 3;
  point T[3];
  T[0] = t1; T[1] = t2; T[2] = t3;
  for (int i = 0; i < N; i++) {
    if (between(T[i], p, T[(i+1) % N])) return -1;
    a += angle(T[i], p, T[(i+1) % N]);
  }
  return cmp(a) != 0;
}


////////////////////////////////////////////////////////////////////////////////
// Calcula a distância do ponto r ao segmento pq.
//
double seg_distance(point p, point q, point r) {
  point A = r - q, B = r - p, C = q - p;
  double a = A * A, b = B * B, c = C * C;
  if (cmp(b, a + c) >= 0) return sqrt(a);
  else if (cmp(a, b + c) >= 0) return sqrt(b);
  else return fabs(A % B) / sqrt(c);
}

int intersectCircleLine(circle &circ, line &l, point &p1, point &p2) {
  //linha vertical
    if (l.b == 0) {
      p1.x = p2.x = -l.c;
      double a = 1.0;
      double b = -2.0*circ.center.y;
      double c= (p1.x - circ.center.x) * (p1.x - circ.center.x)+ circ.center.y*circ.center.y -
	circ.r*circ.r;
      double delta = b*b - 4*a*c;
      int comp = cmp(delta);
      if (comp < 0) 
	return NO;
      if (!comp) { 
	p1.y = -b / (2.0*a);
	return TAN;
      } else {
	p1.y = (-b+sqrt(delta)) / (2.0*a);
	p2.y = (-b-sqrt(delta)) / (2.0*a);
	return SEC;
      }	  
    }else {    
      double a = (1+l.a*l.a);
      double b = (-2*circ.center.x + 2*l.a*l.c - 2* l.a*circ.center.y);
      double c = (circ.center.x * circ.center.x + circ.center.y * circ.center.y + l.c*l.c - 
	2*l.c*circ.center.y - circ.r * circ.r);
      double delta = b*b - 4*a*c;
      int comp = cmp(delta);
      if (comp < 0) 
	return NO;
      if (!comp) { 
	p1.x = -b / (2.0*a);
	p1.y = l.a*p1.x + l.c;
	return TAN;
      } else {
	p1.x = (-b+sqrt(delta)) / (2.0*a);
	p1.y = l.a*p1.x + l.c;
	p2.x = (-b-sqrt(delta)) / (2.0*a);
	p2.y = l.a*p2.x + l.c;
	return SEC;
      }    
    }
}

inline double degreeToRadian(double d) {
    return ((d*PI) / 180.0);
}

point canhao;
circle nlog;
double aEsp, aTiro;

double calculSetor(point &p1, point &p2) {
    double a = dist(nlog.center, p1);
    double b = dist(nlog.center, p2);
    double c = dist(p1, p2);
    double aC = acos((a*a + b*b - c*c)/(2.0*a*b));
    return ((nlog.r*nlog.r) / 2.0) * (aC - sin(aC));
}


int main() {
  while (true) {
      scanf("%lf %lf %lf", &nlog.center.x, &nlog.center.y, &nlog.r);
      if (!nlog.center.x && !nlog.center.y && !nlog.r)
	break;
      scanf("%lf %lf %lf %lf", &canhao.x, &canhao.y, &aTiro, &aEsp);
      line l1, l2;
      aTiro = degreeToRadian(aTiro);
      aEsp = degreeToRadian(aEsp);
      double aReta1 = aTiro-(aEsp/2.0);
      if (cmp(aReta1) < 0)
	 aReta1 = 2.0*PI + aReta1;
      double aReta2 = aTiro+(aEsp/2.0) ;
      if (cmp(aReta2, 2.0*PI) >= 0)
	 aReta2 -= (2.0*PI);
      point2Line(canhao, tan(aReta1), l1);
      point2Line(canhao, tan(aReta2), l2);

      double infY = INF;
      if (cmp(aReta1, PI) >= 0)
	infY = -INF;
      point p1((l1.b*infY - l1.c) / l1.a, infY);
      if (!cmp(l1.a)) {
	  p1.x = infY;
	  p1.y = l1.c;
      }

      infY = INF;
      if (cmp(aReta2, PI) >= 0)
	infY = -INF;
      point p2((l2.b*infY - l2.c) / l2.a, infY);
      if (!cmp(l2.a)) {
	  p2.x = infY;
 	  p2.y = l2.c;
      }
      double d1 = seg_distance(canhao, p1, nlog.center);
      double d2 = seg_distance(canhao, p2, nlog.center);
      double area = 0.0;
      int comp1 = cmp(d1, nlog.r), comp2 = cmp(d2, nlog.r);
      point secA1, secB1, secA2, secB2;	    
      intersectCircleLine(nlog, l1, secA1, secB1);
      intersectCircleLine(nlog, l2, secA2, secB2);
      if (comp1 < 0) {
	  if (comp2 < 0) {
	    if (between(canhao, secA1, p1) && between(canhao, secB1, p1) &&
		between(canhao, secA2, p2) && between(canhao, secB2, p2)) {	      
		if (!inPoly(nlog.center, canhao, p1, p2)) 
		  area = fabs(calculSetor(secA1, secB1)-calculSetor(secA2, secB2));
		else  area = (PI * nlog.r * nlog.r) - calculSetor(secA1, secB1) - calculSetor(secA2, secB2);		
	    }
	  } else {
	     if (between(canhao, secA1, p1) && between(canhao, secB1, p1)) {
		if (!inPoly(nlog.center, canhao, p1, p2)) 
		  area = calculSetor(secA1, secB1);
		else  area = (PI * nlog.r * nlog.r) - calculSetor(secA1, secB1);		
	     }
	  } 
      }else {
	  if (comp2 < 0) {
	     if (between(canhao, secA2, p2) && between(canhao, secB2, p2)) {
		if (!inPoly(nlog.center, canhao, p1, p2)) {
		   area = calculSetor(secA2, secB2);
		}
		else  area = (PI * nlog.r * nlog.r) - calculSetor(secA2, secB2);		
	     }
	  } else {
	     if (!inPoly(nlog.center, canhao, p1, p2)) {
		area = 0.0;
	     } else  area = PI * nlog.r * nlog.r;
	  } 
      }
      printf("%.1lf\n", area);
  }
  return 0;
}