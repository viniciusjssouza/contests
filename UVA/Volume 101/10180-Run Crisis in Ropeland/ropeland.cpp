#include<iostream>
#include<cmath>
#include<algorithm>

const double PI = 3.141592654;

using namespace std;

struct Point
{
	double x;
	double y;
	Point(double x = 0, double y = 0):x(x), y(y){}
};

struct Line
{
	double a;
	double b;
	double c;
	Line(double a = 0, double b= 0, double c=0): a(a), b(b),c(c){}
};

const double EPS = 1e-10;
int N;
Point p1, p2, origem(0,0);
double raio;

double arredonda(double num, int precisao=3)
{
	double fatorPrecisao = pow(10.0, (double)precisao);
	double x = ( num * fatorPrecisao)+ 0.5;
	x = floor(x);
	return (x / fatorPrecisao);
}

inline int cmp(double x, double y = 0, double tol = EPS) 
{
     return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

/* Reta: by = ax + c */
inline void pointToLine(Point &p1, Point &p2, Line &l)
{
	if (!cmp(p1.x, p2.x))
	{
		l.a = 1;
		l.b = 0;
		l.c = p1.x;
	}
	else
	{
		l.a = ((p2.y - p1.y) / (p2.x - p1.x));
		l.b = 1.0;
		l.c = (p1.y - l.a*p1.x);	
	}
}

inline double euclidianDist(Point &p1, Point &p2)
{
	return ( sqrt( pow((p2.x-p1.x), 2.0) + pow((p2.y-p1.y), 2.0) ) );	
}

inline bool intercepta()
{
	Line l;
	pointToLine(p1, p2, l);
	double a = (l.a + l.b);
	double b = 2.0 * l.a *l.c;
	double c = (l.c*l.c - raio*raio * l.b*l.b);
	double delta = (b*b - 4*a*c);
	return (cmp(delta) > 0);			
} 

inline bool isTangent(Point &t, Point &p)
{
	Line l1,l2;
    pointToLine(p, t, l1), pointToLine(t, origem, l2);
	//printf("Olha aqui: %lf %lf\n", l1.a, l2.a);
	if (cmp(l1.a) == 0)
		return(cmp(l2.b) == 0);
	else if (cmp(l2.a) == 0)
		return(cmp(l1.b) == 0);
	else
		return (cmp(l1.a, (-1.0 / l2.a)) == 0);	
}

inline void intersectionPoints(Point &p, Point &t1, Point &t2)
{
	double a = (p.x*p.x + p.y*p.y);
	double b = -2.0*raio*raio*p.x;
	double c = raio*raio - p.y*p.y*raio;
	double delta = b*b - 4*a*c;
	double sol1 = (-b + sqrt(delta))/ (2.0*a);
	double sol2 = (-b - sqrt(delta))/ (2.0*a);
	t1 = Point(sol1, sqrt(raio*raio-sol1*sol1));
	if (!isTangent(t1, p))
		t1.y = -t1.y;
	t2 = Point(sol2, sqrt(raio*raio-sol2*sol2));	
	if (!isTangent(t2, p))
		t2.y = -t2.y;
}

inline double getArc(Point &p1, Point &p2)
{
	if (cmp(p1.x, p2.x) == 0)
	{	
		//cout << "Entrei x = x\n";
		if (cmp(p1.y, -p2.y) == 0)
				return (PI*raio);
		return 0;
	}
	else if (cmp(p1.y, p2.y) == 0)
	{
		//cout << "Entrei y= y\n";
		if (cmp(p1.x, -p2.x) == 0)
			return (PI*raio);
		return 0;
	}
	double c = euclidianDist(p1, p2);
	double a = euclidianDist(p1, origem);
	double b = euclidianDist(p2, origem);
	double teta = acos( (b*b + c*c - a*a) / (2.0*c*b) );	
	//cout << "Teta = " <<  teta << endl;
	return (raio*teta);
}

int main()
{
	scanf("%d", &N);
	while (N--)
	{
		scanf("%lf %lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y, &raio);
		if (!cmp(p1.x, p2.x) && !cmp(p1.y, p2.y))
		{
			printf("0.000\n");
			continue;
		}
		double result;
		if (intercepta())
		{
			Point t11, t12, t21, t22;
			intersectionPoints(p1, t11, t12);
			intersectionPoints(p2, t21, t22);
/*
			cout << t11.x << " " << t11.y << endl;
			cout << t12.x << " " << t12.y << endl;
			cout << t21.x << " " << t21.y << endl;
			cout << t22.x << " " << t22.y << endl;
*/		
			double arc1 = getArc(t11, t21);
			double arc2 = getArc(t11, t22);
			double arc3 = getArc(t12, t21);
			double arc4 = getArc(t12, t22);			
/*
			cout << "Arcs: \n";
			cout << arc1 << endl;
			cout << arc2 << endl;
			cout << arc3 << endl;
			cout << arc4 << endl;
*/	
			result = min(arc1, arc2);
			result = min(result, arc3);
			result = min(result, arc4);
			if (!cmp(result,arc1))
				result += (euclidianDist(p1, t11) + euclidianDist(p2, t21));
			else if (!cmp(result,arc2))
				result += (euclidianDist(p1, t11) + euclidianDist(p2, t22));
			else if (!cmp(result,arc3))
				result += (euclidianDist(p1, t12) + euclidianDist(p2, t21));			
			else
				result += (euclidianDist(p1, t12) + euclidianDist(p2, t22));			
		}
		else
			result = euclidianDist(p1, p2);
		printf("%.3lf\n", arredonda(result));				
	}

	return 0;
}

