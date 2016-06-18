/***** Formulas Uteis ********/
Atriangulo = 0.5 * a.b.senC
Lei dos cossenos: a^2 = b^2 + c^2 - 2.b.c.cosA
Lei dos senos: (a / senA) = (b / senB) = (c / senC)
Setor circular: (r^2 / 2)(o - sen(o));
Produto interno: a.b = |a|.|b|.cosAB
// heron
incentro(a,b,c){
	s=(a+b+c)/2.0000;
    r=sqrt((s-a)*(s-b)*(s-c)/s);
}

/*********** Poligonos ***************/
Test for concave/convex polygon

For a convex polygon all the cross products of adjacent edges will be the same 
sign, a concave polygon will have a mixture of cross product signs. 


///// Descobre o poligono convexo com o maior numero de vertices ////////
/// O(n^3)
bool fcmp(const point &a, const point &b) {
	float v = atan2(a.y, a.x) - atan2(b.y, b.x);
	return v <= 0;
} 

bool antiHorario(point &base, point &a, point &b) {
	point vetorA = point(a.x - base.x, a.y - base.y);
	point vetorB = point(b.x - base.x, b.y - base.y);
	return (vetorA % vetorB) > 0.0;
}

int main() {
	int tcase = 1;
	while(true) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 1; i <= N; i++) {
			scanf("%d %d", &pontos[i].x, &pontos[i].y);
		}
		sort(pontos+1, pontos+N+1, fcmp);
		pontos[0].x = pontos[0].y = 0;		
		int maxv = 1;
		for (int i = 1; i <= N; i++) {
			dp[i][0] = 1;
			for (int j = 1; j < i; j++) {
				dp[i][j] = 0;
				for (int k = 0; k < j; k++) {
					if (dp[j][k] > dp[i][j] && antiHorario(pontos[i], pontos[k], pontos[j]))
						dp[i][j] = dp[j][k];
				}
				dp[i][j]++;
				if (dp[i][j] > maxv)
					maxv = dp[i][j];
			}
		}

/**************************************/


#define INF 0x7FFFFFFF
#define all(v) (v).begin(), (v).end()
#define PI 3.14159265358979323846

const double EPS = 1e-10;
inline int cmp(double x, double y = 0, double tol = EPS){
   return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

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

struct point {
   double x, y;
   point(double x = 0, double y = 0): x(x), y(y) {}
   point operator +(point q) { return point(x + q.x, y + q.y); }
   point operator -(point q) { return point(x - q.x, y - q.y); }
   point operator *(double t) { return point(x * t, y * t); }
   point operator /(double t) { return point(x / t, y / t); }
   /*produto interno */
   double operator *(point q) { return x * q.x + y * q.y; }
   /* produto vetorial */
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


/* Calcula o angulo entre os vetores qp e qr
   ATENCAO: o resultado pode ser negativo!
 */
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


inline int ccw(point p, point q, point r) 
{
   return cmp((p - r) % (q - r));
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


inline double degreeToRadian(double d) {
    return ((d*PI) / 180.0);
}

inline double dist(Point &a, Point &b) {
   return sqrt((double)pow((a.x-b.x), 2.0) + (double)pow((a.y-b.y), 2.0));
}

double distPoint2Line(point &p, line &l) {
    line l2;
    point2Line(p, (-1.0 / l.a), l2);
    point pi;
    intersectPoint(l, l2, pi);
    return dist(p, pi);
}


///////////////////////////////////////////////////////////////////////////////
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

/* Calcula os pontos de interseccao entre uma reta e uma
   circunferencia.
*/
#define NO 0
#define TAN 1
#define SEC 2
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


bool intersectPoint(line &l1, line &l2, point &p) {
    if (sameLine(l1, l2)) {
	p = point(0,0);
	return true;
    }
    if (parallel(l1,l2))
      return false;
    p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
    if (cmp(l1.b, 0.0))
      p.y = -(l1.a * (p.x) + l1.c) / l1.b;
    else
      p.y = -(l2.a*p.x + l2.c) / l2.b;
}


// decide se duas retas sao paralelas
bool parallel(line &l1, line &l2) {
    return ( !cmp(l1.a, l2.a) && !cmp(l1.b, l2.b));
}

void point2Line(point &p1, point &p2, line &l) {
    if (!cmp(p1.x, p2.x)) {
	l.a = 1.0; l.b = 0.0;
	l.c = -p1.x;		
    } else {
	l.b = 1.0;
	l.a = -(p1.y - p2.y) / (p1.x-p2.x);
	l.c = -(l.a * p1.x) - (l.b * p1.y);
    }
    l.c = -l.c;
    l.a = -l.a;
}

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


bool sameLine(line &l1, line &l2) {
    return (parallel(l1,l2) && !cmp(l1.c, l2.c));
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




/***************** Encontra o smallest bounding rectangle ********************/
/****************************************************************************/
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

double calculArea(){
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


/******************************************************************************/


