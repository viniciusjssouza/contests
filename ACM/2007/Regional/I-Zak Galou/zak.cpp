/*****************************************************************************************
* I - Zak Galou - Maratona de Programacao - Regional 2007
*
* Autor: Vinicius J. S. de Souza
* Data: 15/09/2009
* Tecnicas utilizadas: dijkistra + algoritmo da mochila -->minima<--
***********************************************************************************/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define MAX 987654321
#define MAX64 9876543210000LL

int N, G, K, M;

typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pii64;
typedef vector<vector<int> > Grafo;

int64 getDanosMin(Grafo &g, vector<int64> &monstros)
{
	vector<int64> distance(N, MAX64);
    priority_queue<pii64, vector<pii64>, greater<pii64> > fila;
	distance[0] = monstros[0];
	fila.push(pii64(monstros[0], 0));

	while (!fila.empty())
	{
		pii top = fila.top();
		fila.pop();
		int v = top.second;
		int64 d = top.first;
		if (d <= distance[v])
		{
			for (int i = 0; i < g[v].size(); i++)
			{
				int v2 = g[v][i];
				int64 cost = monstros[g[v][i]];
				if (distance[v2] > distance[v] + cost)
				{
					distance[v2] = distance[v] + cost;
					fila.push(pii(distance[v2], v2));
				}
			}
		}
	}
	return distance[N-1];	
}

void getManaMin(vector<int> &dp, vector<pii> &magic, int danos)
{
	dp[0] = 0;
	for (int64 i = 1; i <= danos; i++)
		for (int k = 0; k < M; k++)
		{
			if ( (i - magic[k].second) < 0)
				dp[i] = min(dp[i], magic[k].first);
			else 
				dp[i] = min(dp[i], (dp[i-magic[k].second] + magic[k].first) );
		}	
}

int main()
{
	while (true)
	{
		scanf("%d %d %d %d", &M, &N, &G, &K);
		if (!M && !N && !G && !K) break;
		Grafo g(N, vector<int>());
		vector<pii> magic(M, pii(0,0));
		vector<vector<int> > monstros(N, vector<int>());
		for (int i = 0; i < M; i++)
			scanf("%d %d", &magic[i].first, &magic[i].second);
		for (int i = 0; i < G; i++)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			g[x-1].push_back(y-1);
			g[y-1].push_back(x-1);
		}
		int64 maiorDano = 0;
		for (int i = 0; i< K; i++)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			monstros[x-1].push_back(y);
			if (y > maiorDano)
				maiorDano = y;
		}
		vector<int> dp(maiorDano+1, MAX);
		getManaMin(dp, magic, maiorDano);
		vector<int64> mana(N, 0);

		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < monstros[i].size(); k++)
				mana[i] += (int64)dp[monstros[i][k]];
		}
		int64 danos = getDanosMin(g, mana);
		if (danos >= MAX64)
			printf("-1\n");
		else
			printf("%llu\n", danos);	

	}
	return 0;
}

