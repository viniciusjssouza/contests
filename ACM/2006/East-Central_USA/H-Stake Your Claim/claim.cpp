#include<iostream>
#include<cstdio>
#include<string.h>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

#define INF 0x3fffffff

typedef pair<int,int> pii;

int N;
char grid[8][8];
bool visited[8][8];
bool used[11];
pii sol;

int maximize(int player, vector<pii> &empty, int nivel, int maxv, int minv);
int minimize(int player, vector<pii> &empty, int nivel, int maxv, int minv);

int ccSize(int lin, int col) {
	visited[lin][col] = true;
	queue<pii> fila;
	fila.push(pii(lin,col));
	int count = 0;
	while (!fila.empty()) {
		pii pos = fila.front();
		int i = pos.first, k = pos.second; 
		fila.pop();
		count++;
		if (k+1 < N && !visited[i][k+1] && grid[i][k+1] == grid[i][k]) {
			visited[i][k+1] = true;
			fila.push(pii(i, k+1));
		}
		if (i-1 >= 0 && !visited[i-1][k] && grid[i-1][k] == grid[i][k]) {
			visited[i-1][k] = true;
			fila.push(pii(i-1, k));
		}
		if (k-1 >= 0 && !visited[i][k-1] && grid[i][k-1] == grid[i][k]) {
			visited[i][k-1] = true;
			fila.push(pii(i, k-1));
		}
		if (i+1 < N && !visited[i+1][k] && grid[i+1][k] == grid[i][k]) {
			visited[i+1][k] = true;
			fila.push(pii(i+1, k));
		}
	}
	return count;
}

int eval(int player) {
	memset(visited, false, sizeof(visited));
	int maior = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k <N; k++) {
			if (!visited[i][k] && grid[i][k] == (player+'0')) {
				maior = max(maior, ccSize(i,k));
			}
		}
	}
	return maior;
}

int maximize(int player, vector<pii> &empty, int nivel, int maxv, int minv) {
	if (empty.size() == nivel) {
		return eval(player) - eval(!player);
	}
	for (int i = 0; i < empty.size(); i++) {
		if (!used[i]) {
			used[i] = true;
			grid[empty[i].first][empty[i].second] = player + '0';
			int temp = minimize(player, empty, nivel+1, maxv, minv);
			grid[empty[i].first][empty[i].second] = '.';
			used[i]= false;
			if (temp > maxv) {
				maxv = temp;
				if (nivel == 0)
					sol = empty[i];
			}			
			if (maxv >= minv) 
				return minv;
		}
	}
	return maxv;
}

int minimize(int player, vector<pii> &empty, int nivel, int maxv, int minv) {
	if (empty.size() == nivel) {
		return eval(player) - eval(!player);
	}
	for (int i = 0; i < empty.size(); i++) {
		if (!used[i]) {
			used[i] = true;
			grid[empty[i].first][empty[i].second] = (!player) + '0';
			int temp = maximize(player, empty, nivel+1, maxv, minv);
			grid[empty[i].first][empty[i].second] = '.';
			used[i]= false;
			if (temp < minv) {
				minv = temp;
			}
			if (minv <= maxv)
				return maxv;			
		}
	}
	return minv;
}


int main() {
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		for(int i = 0; i < N; i++) {
			scanf("%s", grid[i]);
		}
		int p1 = 0, p0 = 0;
		int max1 = 0, max0 = 0;
		vector<pii> empty;
		for (int i = 0; i <N; i++) {
			for (int k = 0; k < N; k++) {
				if (grid[i][k] == '1'){
					p1++;
				}
				else if (grid[i][k] == '0') {
					p0++;
				}
				else
					empty.push_back(pii(i,k));
			}
		}
		int best;
		memset(used, false, sizeof(used));
		if (p1 == p0)
			best = maximize(0, empty, 0, -INF, INF);
		else 
			best = maximize(1, empty, 0, -INF, INF);
		printf("(%d,%d) %d\n", sol.first, sol.second, best);
	}
	return 0;
}
