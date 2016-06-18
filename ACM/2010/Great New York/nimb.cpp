/************************************************************************
* ACM 2010 - Greater New York - Nim-B Sum
*
* Autor: Vinicius J. S. Souza
* Data: 13/07/2011
* Tecnicas: transformacao de bases.
***********************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>

#define para(i, N) for(int i = 0; i < N; i++)
#define debug false
using namespace std;

/** Obs: o numero deve ser lido do final do vector para o inicio.*/
void toBaseB(int x, int b, vector<int> &num) {
	int q = x, r = 0;
	while (q >= b) {
		r = q % b;
		q = q / b;
	  	num.push_back(r);
	} 	
	num.push_back(q);
} 

long int fromBaseB(const vector<int> &num, int b) {
	long int dec = 0;
	long int mult = 1;
	for (int i = 0; i < num.size(); i++) {
		dec += (num[i]*mult);
		mult *= b;
	}
	return dec;
}

int main() {
	int P;
	scanf("%d", &P);
	for (int p = 0; p < P; p++) {
		int n, b, x, y;;
		scanf("%d %d %d %d", &n, &b, &x, &y);
		vector<int> nx; 
		toBaseB(x,b, nx);
		vector<int> ny;
		toBaseB(y,b, ny);
		int sz = max(nx.size(), ny.size());
		
		if (debug) {
			para(i, nx.size()) {
				cout << nx[i] << " ";
			}
			cout << endl;
			para(i, ny.size()) {
				cout << ny[i] << " ";
			}
			cout << "--------\n";
		}

		vector<int> res(sz);
		para(i, sz) {
			if (i >= nx.size()) {
				res[i] = ny[i];
			} else if (i >= ny.size()) {
				res[i] = nx[i];
			} else {
				res[i] = (nx[i] + ny[i]) % b;
			}			
		}
		cout << n << " " << fromBaseB(res, b) << endl;
	}
	return 0;
}
