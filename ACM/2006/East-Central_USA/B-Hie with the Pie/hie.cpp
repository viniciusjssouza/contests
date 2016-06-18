#include<cstdio>
#include<string.h>
#include<algorithm>

#define INF 0x3fffffff

using namespace std;

int grafo[11][11], N, visited[11][11], allVisited, best;
bool used[11];

void solve(int v, int dist, int vis) {
	if (vis == allVisited) {
		best = min(best, dist + grafo[v][0]);
		return;
	}
	used[v] = true;
	for (int i = 0; i <= N; i++) {
		if (!used[i] && dist+grafo[v][i] < best) {
			solve(i, grafo[v][i]+dist, (visited[v][i] | vis));			
		}
	}
	used[v] = false;	
}

int nVisited(int v) {
	int conta = 0;
	for (int i = 0; i <= N; i++) {
		if (v & 1)
			conta++;
		v = v >> 1;	  
	}
	return conta;
}

int main() {
	while (1) {
		scanf("%d", &N);
		if (!N)
			break;
		memset(grafo, INF, sizeof(grafo));
		memset(visited, 0, sizeof(visited));
		allVisited = (1 << (N+1)) - 1;
		for(int i=0; i<=N; i++) {
	   		for(int k=0; k<=N; k++){  
				scanf("%d",&grafo[i][k]);
				visited[i][k] = (visited[i][k] | (1 << i) | (1 << k));
			}
		}
		
		// floyd-warshall all-pairs shortest distance
		for (int k = 0; k <= N; k++) {
			for (int i= 0; i <= N; i++) {
				for (int j = 0; j <= N; j++) {
					int temp = grafo[i][k] + grafo[k][j];
					if (temp < grafo[i][j]) {
						grafo[i][j] = temp;
						visited[i][j] = visited[i][k] | visited[k][j];
					} else if (temp == grafo[i][j]) {
						int x = visited[i][k] | visited[k][j];
						if (nVisited(x) > nVisited(visited[i][j])) {
							grafo[i][j] = temp;
							visited[i][j] = x;
						}
					}
				}
			} 
		}
/*
		printf("%d\n", allVisited);
		for(int i=0; i<=N; i++) {
	   		for(int k=0; k<=N; k++){  
				printf("%d ", grafo[i][k]);
			}
			printf("\n");
		}		
		printf("--------------\n");
		for(int i=0; i<=N; i++) {
	   		for(int k=0; k<=N; k++){  
				printf("%d ", visited[i][k]);
			}
			printf("\n");
		}
*/
		memset(used, false, sizeof(used));
		best = INF;
		solve(0, 0, 0);
		printf("%d\n",best); 
	}		
} 
