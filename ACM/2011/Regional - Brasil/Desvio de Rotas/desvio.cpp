/***************************************************************************
* ACM - Regional Brasileira 2011 - Desvio de Rotas
*
* Autor: Vinicius J. S. Souza
* Data: 06/10/2011
* Tecnicas: Pontes em grafos e conectividade.
***************************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>

using namespace std;

#define para(i,B,N) for(int i = B; i < N; i++)

typedef pair<int,int> pii;
typedef vector<vector<pii> > grafo;

bool visited[1010];
int N, M;	

int V, E;
int bridgeCont, cnt;

void searchC(grafo &g, vector<int> &ord, vector<int> &low, pii par) {
	int v = par.second;
	ord[v] = cnt++;
	low[v] = ord[v];
	for (int i = 0; i < g[v].size(); i++) {
		if (bridgeCont)
			return;
		int v2 = g[v][i].first;
		if (ord[v2] == -1)
		{
			searchC(g, ord, low, pii(v,v2));
			if (low[v] > low[v2])
				low[v] = low[v2];
			if (low[v2] == ord[v2] && g[v][i].second < 2)
			{
				bridgeCont++; // v-v2 eh uma ponte
				return;
			}			
		}
		else if (v2 != par.first)
			if (low[v] > ord[v2]) 
				low[v] = ord[v2];  		
	}	
}

bool haPontes(grafo &g) {
	vector<int> ord(N, -1), low(N, -1);
	bridgeCont = 0, cnt = 0;
	for (int i = 0; i < N; i++)	{
		if (bridgeCont)
			return true;
		if (ord[i] == -1)
			searchC(g, ord, low, pii(i,i));
	}
	return (bridgeCont > 0);
}

void explore(grafo &g, int v, bool dir) {
	visited[v] = true;
	
	para(i,0,g[v].size()) {
		int w = g[v][i].first;
		int t = g[v][i].second;
		if (!visited[w] && (t > 0 || (!dir))) {
			explore(g,w,dir);
		}
	}
}

void dfs(grafo &g, int begin, bool dir){
	para(i,0,N)
		visited[i] = false;
	explore(g, begin, dir);
}

int main() {
	while (scanf("%d %d", &N, &M) == 2) {
		grafo g(N);
		int A,B;
		para (i, 0, M) {
			int a,b,T;
			scanf("%d %d %d", &a, &b, &T);			
			a--; b--;
			if (!i) {
				A = a;
				B = b; 
				continue;
			}						
			if (T == 1) {
				g[a].push_back(pii(b,1));	
				g[b].push_back(pii(a,0));			
			} else if (T == 2) {
				g[b].push_back(pii(a,2));
				g[a].push_back(pii(b,2));	
			}			
		}	
		// sem mudancas
		dfs(g,A,true);
		if (visited[B]) {
			dfs(g,B,true);
			if (visited[A]) {
				cout << "-" << endl;
				continue;
			}				
		}
		// invertendo algumas ruas
		dfs(g,A,false);
		int conta = 0;
		para (i,0,N) {
			if (visited[i]) {
				conta++;
			}
		}
		if (conta >= N && !haPontes(g)) {
			cout << "1" << endl;	
		}
		// todas para mao dupla
		 else if (conta >= N) {
			cout << "2" << endl;
		} else {
			cout << "*" << endl;
		}		

	}			
	return 0;
}
