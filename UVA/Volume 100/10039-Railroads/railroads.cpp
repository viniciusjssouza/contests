/******************************************************************
UVA 10039 - Railroads

Autor: Vinicius J. S. Souza
Data: 21/07/2011
Tecnicas: time dependent shortest path.
Dificuldade: 9 (1-10)
*******************************************************************/

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
#define UM_DIA 1440
#define INF 0x3f3f3f3f
using namespace std;

string cids[102];
struct Train {
public:
	int part;
	int cheg;
	Train(int p, int c) { part = p; cheg = c;}
	Train(){}
	bool operator()(const Train &a, const Train &b) {
		return a.b <
	}	  
};
typedef pair<int, int> pii;
typedef vector<vector<vector<Train> > > Grafo;
map<string, int> ids;

int parseH(const string &hor) {
	return (atoi(hor.substr(0,2).c_str())*60 + atoi(hor.substr(2,2).c_str()));
}

void h2str(int hor, char* &str) {
	str = new char[5];
	str[4] = '\0';
	int h = hor / 60;
	int m = hor % 60;
	if (h < 10) {
		str[0] = '0';
		str[1] = h + '0';
	} else {
		str[0] = (h / 10) + '0';
		str[1] = (h % 10) + '0';
	}
	if (m < 10) {
		str[2] = '0';
		str[3] = m + '0';
	} else {
		str[2] = (m / 10) + '0';
		str[3] = (m % 10) + '0';
	} 
}

int C;
int distancia[102];

int f(Grafo &g, int t, int v, int w) {
	int  best = INF;
	para(i, g[v][w].size()) {
		int peso = INF;
		if (g[v][w][i].part < t) {
			peso = UM_DIA - t + g[v][w][i].cheg; 
		} else {
			peso = g[v][w][i].cheg - t;
		}	
		if (peso < best) {
			best = peso;
		}
	}
	return best;
}

void shortestPath(Grafo &g, int ori, int dest, int start) {
	memset(distancia, INF, sizeof(distancia));
	priority_queue<pii, vector<pii>, greater<pii> > fila;
	distancia[ori] = 0;
	fila.push(pii(0, ori));

	while (!fila.empty()) {
		pii top = fila.top();
		fila.pop();
		int v = top.second, d = top.first;
		if (debug) {
			printf("Em %s com d=%d\n", cids[v].c_str(), d);
		}
		if (v == dest) {
			return;
		}
		for (int c = 1; c <= C; c++) {
			if (g[v][c].size() > 0) {
				int v2 = c;
				int cost = f(g, start + d, v, v2);
				if (start+d+cost >= 1440)
					continue;
				if (distancia[v2] > distancia[v] + cost) {
					distancia[v2] = distancia[v] + cost;
					fila.push(pii(distancia[v2], v2));
				}
			}
		}
	}
}

int main() {
	int N;
	scanf("%d", &N);
	para(n,N) {
		scanf("%d", &C);
		for(int c = 1; c <= C; c++) {
			cin >> cids[c];
			ids[cids[c]] = c;
		}
		int T;
		scanf("%d", &T);
		Grafo G(C+1, vector<vector<Train> >(C+1));
		para(t, T) {
			int L, part;
			string hor, ant, dest;
			scanf("%d", &L);	
			cin >> hor >> ant;
			part = parseH(hor);
			for (int l = 1; l < L; l++) {
				cin >> hor >> dest;   				
				Train train(part, parseH(hor));
				part = train.cheg;
				G[ids[ant]][ids[dest]].push_back(train);
				ant = dest;						

			}
		}
		string hor, oriStr, destStr;
		cin >> hor >> oriStr >> destStr;
		int start = parseH(hor), ori = ids[oriStr], dest = ids[destStr];		
		if (debug) {
			for(int c = 1; c <= C; c++) {
				printf("------ %s ------\n", cids[c].c_str());
				for(int k = 1; k <= C; k++) {
					para(m, G[c][k].size()) {
						printf("%d %d %s\n", G[c][k][m].part, G[c][k][m].cheg, cids[k].c_str());
					}
				}
			}
			cout << ori << " para "  << dest << " as " << start << endl;
		}
		int minDur = INF, bestPart = -1;
		for (int c = 1; c <= C; c++) {
			para(e, G[ori][c].size()) {
				if (debug) {
					printf("SP para %s as %d\n", cids[c].c_str(), G[ori][c][e].cheg);
				}
				if (G[ori][c][e].part < start)
					continue;
				shortestPath(G, c, dest, G[ori][c][e].cheg);	
				distancia[dest] += (G[ori][c][e].cheg - start);
				if (distancia[dest] < minDur || (distancia[dest]==minDur 
					&& G[ori][c][e].part > bestPart)) {
					if (debug) {
						printf("Update %d %d\n", distancia[dest], G[ori][c][e].part);
					}
					minDur = distancia[dest];
					bestPart = G[ori][c][e].part;
				}
			}
		}
		printf("Scenario %d\n", n+1);
		if (minDur < INF) {
			char* h1,*h2;
			h2str(bestPart, h1);
			h2str(start+minDur, h2);
			printf("Departure %s %s\n", h1, oriStr.c_str());
			printf("Arrival   %s %s\n", h2, destStr.c_str());
			delete h1;
			delete h2;
		} else {
			cout << "No connection\n";
		}	
		cout << endl;
		ids.clear();
	}
	return 0;
}
