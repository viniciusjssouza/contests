/*******************************************************************
* Piscina - Regional da Maratona - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 24/02/2010
* Tecnicas: logica greedy
* Dificuldade(1-10): 8  
*********************************************************************/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<deque>

using namespace std;

#define sizeG	30
#define sizeM	15
#define sizeP	5
#define precoG  0.50
#define precoM  0.15
#define precoP  0.02  

typedef pair<int,int> rect;

double X, Y, Z;
int P, M, G, p, m, g;
deque<rect> r;

void fill(int V, int &v, int sizeV) {
	int nRect = r.size();
	for (int i = 0; i < nRect && v < V; i++) {
		int x = r.front().first, y = r.front().second;
		r.pop_front();
		if (x < sizeV || y < sizeV) {
     		r.push_back(rect(x,y));	
			continue;			
		}			
		int fillX = x / sizeV;
		int sobraX = x % sizeV;
		int fillY = y / sizeV;	
		int sobraY = y % sizeV;
		int total = fillX * fillY;
		if (v+total <= V)  {
			v += total;			
			if (sobraX && fillY)
				r.push_back(rect(sobraX, fillY*sizeV));
			if (fillY * sizeV < y)
				r.push_back(rect(x, (y - fillY * sizeV)));
		} else {
			int sX = x - (((V - v) % fillX)*sizeV);
			fillY = ((V-v) / fillX)+1; 
			v = V;
			if (sX > 0 && sX < x) {
				r.push_back(rect(sX, sizeV));				
			}
			if (sobraX && fillY > 1)
				r.push_back(rect(sobraX, (fillY-1)*sizeV));
			if (fillY * sizeV < y)
				r.push_back(rect(x, (y - fillY * sizeV)));
		}
	}
}

bool solveRect() {
	fill(G, g, sizeG);
	fill(M, m, sizeM);	
	fill(P, p, sizeP);
	return (r.empty());
}

int main() {
	while (true) {
		r.clear();
		scanf("%lf %lf %lf", &X, &Y, &Z);
		if (!X && !Y && !Z) 
			break;
		X *= 100;
		Y *= 100;
		Z *= 100;
		p = m = g = 0;
		scanf("%d %d %d", &P, &M, &G);
		r.push_back(rect(X,Z));		
		if (!solveRect()) {
			printf("impossivel\n");
			continue;
		}
		r.push_back(rect(X,Z));		
		if (!solveRect()) {
			printf("impossivel\n");
			continue;
		}
		r.push_back(rect(Y,Z));		
		if (!solveRect()) {
			printf("impossivel\n");
			continue;
		}
		r.push_back(rect(Y,Z));		
		if (!solveRect()) {
			printf("impossivel\n");
			continue;
		}
	r.push_back(rect(X,Y));		
		if (!solveRect()) {
			printf("impossivel\n");
			continue;
		}
		printf("%d %d %d\n", p, m, g);
	}
	return 0;
}
