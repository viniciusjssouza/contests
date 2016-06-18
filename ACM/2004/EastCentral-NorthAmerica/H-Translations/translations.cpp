#include<iostream>
#include<cstring>
#include<string>
#include<map>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<algorithm>

using namespace std;

typedef pair<int,int> pii;
typedef vector<vector<int> > grafo;
typedef vector<vector<int> > vvi;

int N;
int V = 0;
vvi poss;
map<string, int> id1, id2;
string str1[30], str2[30];
int in1[30], in2[30], out1[30], out2[30];
grafo g1(30), g2(30);
int matched[30];
bool used[30];

void insert(grafo &g, map<string, int> &id, string str[], int in[], int out[]) {
	V = 0;
	string sa, sb;
	int v,w;
	for (int i= 0; i < N; i++) {
		cin >> sa >> sb;
		if (id[sa] == 0) {
			id[sa] = v = ++V;
			str[v] = sa;
		}
		else
			v = id[sa];
		if (id[sb] == 0) {
			id[sb] = w = ++V;
			str[w] = sb;
		}
		else
			w = id[sb];
		g[v].push_back(w);
		in[w]++;
		out[v]++;
	}
} 

bool hasEdge(int v, int w, grafo &g) {
	for (int i = 0; i < g[v].size(); i++) {
		if (g[v][i] == w)
			return true;
	}
	return false;
}

bool ok(int v, int w) {
	if (in1[v] != in2[w] || out1[v] != out2[w])
		return false;
	for (int i = 1; i <= V; i++) {
		if (matched[i] != -1) {
			if (hasEdge(v, i, g1) && !hasEdge(w, matched[i], g2))
				return false;
			if (hasEdge(i, v, g1) && !hasEdge(matched[i], w, g2))
				return false;
		}
	}
	return true;
}

bool solve(int nivel) {
	if (nivel > V) {
		return true;
	}
	for (int w = 1; w <= V; w++) {
		if (!used[w] && ok(nivel, w)) {
			used[w] = true;
			matched[nivel] = w;
			if (solve(nivel+1))
				return true;
			used[w] = false;
			matched[nivel] = -1;
		}
	}
	return false;
}

int main() {
	while (true) {
		scanf("%d" , &N);
		if (!N)
			break;
		for (int i = 0; i < 30; i++) {
			in1[i] = in2[i] = out1[i] = out2[i] = 0;
			g1[i].clear();
			g2[i].clear();
			id1.clear();
			id2.clear();
			matched[i] = -1;
		}
		insert(g1,id1, str1, in1, out1);
		insert(g2,id2, str2, in2, out2);

		memset(used, false, sizeof(used));
		memset(matched, -1, sizeof(matched));
		if (!solve(1)) 	
			printf("Sem SOLUCAO!\n");

		sort(str1, str1+V+1);
		for (int i = 1; i <= V; i++) {
			printf("%s/%s\n", str1[i].c_str(), str2[matched[id1[str1[i]]]].c_str());
		}
		putchar('\n');
	}

	return 0;
} 
