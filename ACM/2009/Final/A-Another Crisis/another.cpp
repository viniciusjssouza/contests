/****************************************************************************
* A - Another Crisis - Final Sul-americana 2009
*
* Autor: Vinicius J. S. Souza
* Data: 6/11/2009
* Tecnicas: dfs
**********************************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

typedef vector<vector<int> > Tree;

int N, T;

int dfs(Tree &g, int v)
{
	int tam = g[v].size();
	if (!tam)
		return 1;
	int nSubordinados = ceil((float)(T*tam) / 100.0);
	int soma = 0, maior = -(0x3fffffff);
	vector<int> s;
	for (int i = 0; i < tam; i++) {
		int r = dfs(g, g[v][i]);
		if (i < nSubordinados) {
			s.push_back(r);
			maior = max(maior, r);		
			soma+= r;		
		}
		else if (r < maior){
			s.push_back(r);
			sort(s.begin(), s.end());
			soma = (soma - maior + r);		
			s.pop_back();
			maior = s.back();
		}
	}
	return soma;	
}

int main()
{
	while (true)
	{
		scanf("%d %d", &N, &T);
		if (!N && !T) break;
		Tree g(N+1);
		int x;
		for (int i = 1; i <= N; i++){
			scanf("%d", &x);
			g[x].push_back(i);	
		}
		printf("%d\n", dfs(g, 0));
	}
	return 0;
}

