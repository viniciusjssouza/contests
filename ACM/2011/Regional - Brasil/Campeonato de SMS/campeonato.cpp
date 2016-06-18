/***********************************************************************
* ACM 2011 - Regional Brasileira - Campeonato de SMS
*
* Autor: Vinicius J. S. Souza
* Data: 29/09/2011
* Tecnicas: PD com memoization
*************************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

#define para(i,n,N) for (int i = n; i < N; i++)
const double EPS = 1e-6;
inline int cmp(double x, double y, double tol=EPS) {
	return (x <= y+tol) ? (x+tol < y) ? -1:0:1;
}

#define debug false

using namespace std;

typedef pair<int,int> pii;

string msg;
map<char, pii> keys;
map<char, int> clicks;
vector<pii> press;
double memo[800][4][4][4][4];

double dist(const pii &a, const pii &b) {
	double powy = (a.first-b.first)*(a.first-b.first);
	double powx = (a.second-b.second)*(a.second-b.second);
	return (double)sqrt(powy + powx);
}

double backtrack(int nivel, pii &left, pii &right) {
	if (nivel >= press.size())
		return 0.0;
	pii next = press[nivel];
	if (next == left || next == right)
		return backtrack(nivel+1, left, right);
	if (memo[nivel][left.first][left.second][right.first][right.second] >= 0) {
		return memo[nivel][left.first][left.second][right.first][right.second];
	}
	// obtem o custo de levar a mao esquerda para a proxima tecla
	double t = (double)dist(left, next);
	double esq = backtrack(nivel+1,  next, right) + t;
	// obtem o custo de levar a mao direita para a proxima tecla
	double t2 = (double)dist(right, next);
	double dir = backtrack(nivel+1,  left, next) + t2;
	if (cmp(esq, dir) < 0)  {
		memo[nivel][left.first][left.second][right.first][right.second] = esq;
		return esq;
	} else {
		memo[nivel][left.first][left.second][right.first][right.second] = dir;
		return dir;
	}
}

int main() {
	keys['a'] = keys['b'] = keys['c'] = pii(0,1); // 2
	keys['d'] = keys['e'] = keys['f'] = pii(0,2); // 3
	keys['g'] = keys['h'] = keys['i'] = pii(1,0); // 4
	keys['j'] = keys['k'] = keys['l'] = pii(1,1); // 5
	keys['m'] = keys['n'] = keys['o'] = pii(1,2); // 6
	keys['p'] = keys['q'] = keys['r'] = keys['s'] = pii(2,0); // 7
	keys['t'] = keys['u'] = keys['v'] = pii(2,1); // 8
	keys['w'] = keys['x'] = keys['y'] =  keys['z'] = pii(2,2); // 9
	keys[' '] = pii(3,1);
	keys['#'] = pii(3,2);

	clicks['a'] = clicks['d'] = clicks['g'] = clicks['j'] = clicks['m'] = 
		clicks['p'] = clicks['t'] = clicks['w'] = clicks[' '] = clicks['#'] = 1; 
	clicks['b'] = clicks['e'] = clicks['h'] = clicks['k'] = clicks['n'] = 
		clicks['q'] = clicks['u'] = clicks['x'] = 2;
	clicks['c'] = clicks['f'] = clicks['i'] = clicks['l'] = clicks['o'] = 
		clicks['r'] = clicks['v'] = clicks['y'] = 3;
	clicks['s'] = clicks['z'] = 4;

	while (getline(cin, msg)) {
		if (msg.size() == 0) {
			continue;
		}
		int count = 0;
		press.clear();	
		memset(memo, -100.0, sizeof(memo));	
		para(i, 0, msg.size()) {
			if (i > 0 && keys[msg[i]] == keys[msg[i-1]]) {
				press.push_back(keys['#']);
				count++;
			}
			count += clicks[msg[i]];
			press.push_back(keys[msg[i]]);			
		}
		
		if (debug) {
			printf("---------------\n");
			para(i,0,press.size()) {
				printf("(%d, %d)\n", press[i].first, press[i].second);
			}		
		}
		
		double res = backtrack(0, keys['g'], keys['m']) / 30.0;
		res += 0.2*(double)(count);
		printf("%.2lf\n", res);
	}
	return 0;
}
