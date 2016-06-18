#include <cstdio>
#include <cmath>
#include <map>
#include <set>
#include<vector>
#include<algorithm>


#define EPS 1e-6

using namespace std;

inline int cmp(double x, double y) {
   return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
}

struct point {
   double x, y;
   point(double x = 0, double y = 0): x(x), y(y) {}
   point operator +(const point &q) { return point(x + q.x, y + q.y); }
   point operator -(const point &q) { return point(x - q.x, y - q.y); }
   point operator *(const double &t) { return point(x * t, y * t); }
   point operator /(const double &t) { return point(x / t, y / t); }
   double operator *(const point &q) { return x * q.x + y * q.y; }
   double operator %(const point &q) { return x * q.y - y * q.x; }
   int cmp(const point &q) const {
   if (int t = ::cmp(x, q.x)) return t;
   return ::cmp(y, q.y);
   }
   bool operator ==(const point &q) const { return cmp(q) == 0; }
   bool operator !=(const point &q) const { return cmp(q) != 0; }
   bool operator < (const point &q) const { return cmp(q) < 0; }

};

point circumcenter(point &p, point &q, point &r) {
   point a = p - r, b = q - r, c = point(a * (p + r) / 2, b * (q + r) / 2);
   return point(c % point(a.y, b.y), point(a.x, b.x) % c) / (a % b);
}

double norma(const point &p) { return hypot(p.x, p.y); }

point points[105];

int i, j;


int main(){
	int n,x,y;
	while(true){       
		scanf("%d",&n);
		if(!n)
			break;
		for(int i=0; i<n; i++){;
			scanf("%lf",&points[i].x);
			scanf("%lf",&points[i].y);
		}
		if(n<3)
			printf("%d\n",n);
		int maxc = 0;
		vector<point> centers;
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				/*for(int k=j+1; k<n; k++){
					point A=points[j]-points[i], B=points[j]-points[k];
					if(cmp(abs(A*B),abs(norma(A)*norma(B)))==0){
						continue;
					}
					point center=circumcenter(points[i],points[j],points[k]);
					centers.push_back(center);
				}*/
				sort(points.begin(), pon.end());
				/*for (int k = 1; k < centers.size(); k++) {
					printf("(%.2lf %.2lf)\n", centers[k].x, centers[k].y);
				}
				printf("----------------\n");
				*/int conta = 1;
				for (int k = 1; k < centers.size(); k++) {
					if (centers[k] == centers[k-1])
						conta++;
					else {
						if (conta > maxc)
							maxc = conta;					
						conta = 1;
					} 
				}
				
				                
			}
		}
		printf("%d\n",maxc+2);
	}
}
