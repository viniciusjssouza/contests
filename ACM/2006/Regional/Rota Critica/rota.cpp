/******************************************************************************
* Rotas Criticas - Regional - Maratona 2006
* 
* Autor: Vinicius J. S. Souza
* Data: 18/03/2010
* Tecnicas: dfs
* Dificuldade(1-10): 6
******************************************************************************/
#include<iostream>
#include<string>
#include<cstdio>
#include<map>
#include<deque>
#include<algorithm>

using namespace std;

struct edge {
	int v1;
	int v2;
	int id;
	edge(int v, int w, int i) {
		v1 = v; v2 = w; id = i;
	}
};

deque< deque<edge> > g(110, deque<edge>());
string cities[110];
deque<edge> E;
bool visited[110];
map<string, int> getId;

int cnt;
int N, M;

bool dfs(int id, int v) {
	visited[v] = true;
	if (!v) {
		return true;
	}
	int size = g[v].size();
	for (int i = 0; i < size; i++) {
		if (!visited[g[v][i].v2] && g[v][i].id != id) {
			if (dfs(id, g[v][i].v2)) {
				return true;
			}
		}
	}	
	return false;
}

int main() {
	long s = clock();
	while (true) {
		scanf("%d %d", &N, &M);
		if (!N && !M) break;
		string a,b;
		E.clear();
		getId.clear();
		for (int i = 0;i < N; i++) {
			cin >> cities[i];
			getId[cities[i]] = i;
			g[i].clear();
		}
		for (int i = 0; i < M; i++) {
			cin >> a >> b;
			int aid = getId[a];
			int bid = getId[b];
			edge e(aid,bid,i);			
			g[aid].push_back(e);
			E.push_back(e);
		}
		cnt = 0;
		bool nenhuma = true;
		for (int i = 0; i < M; i++){
			if (!dfs(i, E[i].v1)) {
				printf("%s %s\n", cities[E[i].v1].c_str(), cities[E[i].v2].c_str());
				nenhuma = false;		
			}	
			for (int k = 0; k < N; k++)
				visited[k] = false;	
		}
		if (nenhuma) {
			printf("Nenhuma\n\n");
		} else 
			putchar('\n');
	}
	//cout << (double)(clock()-s) / (double)CLOCKS_PER_SEC << endl;
	return 0;	
}
