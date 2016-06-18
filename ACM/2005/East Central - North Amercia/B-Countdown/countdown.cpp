/*********************************************************************
* Countdown - ACM - North America- East Central - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 20/08/2010
* Tecnicas: dfs + sorting
* Dificuldade(1-10): 5
**********************************************************************/
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>

using namespace std;

typedef pair<int, string> pis;

int N, D;
string nomes[1010];
map<string, vector<string> > tree;

bool cmp(const pis &a, const pis &b) {
	if (a.first > b.first)
		return true;
	if (a.first < b.first)
		return false;
	return (a.second <= b.second);
}

int dfs(string &nome, int depth) {
	if (depth == D-1) {
		return tree[nome].size();
	}
	int soma = 0;
	for (int i = 0; i < tree[nome].size(); i++) {
		soma += dfs(tree[nome][i], depth+1);
	}
	return soma;
}

int main() {
	int t;
	scanf("%d", &t);
	for(int tcase = 1; tcase<= t; tcase++) {
		tree.clear();
		scanf("%d %d", &N, &D);
		for (int i = 0; i < N; i++) {
			int x;
			cin >> nomes[i] >> x;
			for (int k = 0; k < x; k++) {
				string temp;
				cin >> temp;
				tree[nomes[i]].push_back(temp);
			}
		}
/*
		for (int i = 0; i < N; i++) {
			cout << "-------- " <<  nomes[i] << " ---------\n";
			for (int k = 0; k < tree[nomes[i]].size(); k++) {
				cout << tree[nomes[i]][k] << endl;
			}
		}		
*/
		vector<pis> order;
		int i = 0;
		for (i = 0; i < N; i++) {
			int p = dfs(nomes[i], 0);
			order.push_back(pis(p, nomes[i]));
		}
		sort(order.begin(), order.end(), cmp);
		printf("Tree %d:\n", tcase);
		for (int i = 0; i < order.size(); i++) {
			if (i > 2 && order[i].first != order[2].first)
				break;
			printf("%s %d\n", order[i].second.c_str(), order[i].first);
		} 
		if (tcase < t)
			putchar('\n');
	}
	return 0;
}



 
