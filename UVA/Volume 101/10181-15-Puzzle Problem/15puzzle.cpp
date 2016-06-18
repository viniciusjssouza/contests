#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<map>
#include<queue>

using namespace std;

#define MAX 4
#define rptr	54
#define M	3
#define W	1

vector<int> grid(16);
char result[55];
map<vector<int>, bool> proc;
int maxSteps;
//distancia manhataniana de uma configuracao
int mDist()
{
	int distance = 0;
	for (int i = 0; i < 16; i++){
		distance += mDist(grid[i], i);
	}
	return distance;
}

inline int mDist(int n, int pos) {
	int row = pos / 4;
	int col = pos % 4;
	if (!n) {
		return (abs(row-3) + abs(col-3));
	} else {
		int finalRow = (n-1) / 4;
		int finalCol = (n-1) % 4;
		return (abs(row-finalRow) + abs(col-finalCol));			
	}
}

int N;

// verifica se uma dada configuracao possui solucao
bool temSolucao()
{
	int soma = 0;
	int row = 0;
	int limit = MAX * MAX + 1;
	vector<bool> vet(limit, false);
	for (int i = 0; i < MAX; i++)
	{
		for (int k = 0; k < MAX; k++)
		{
			int pos = i*4+k;
			if (!grid[pos])
				row = i+1;
			else if (grid[pos] == 1) vet[1] = true;
			else
			{
				for (int m = 1;  m < grid[pos]; m++)
					if (!vet[m])
						soma++;
				vet[grid[pos]] = true;
				//cout << "Soma:" << soma << endl;		
			}			
		}
	}
	if (!((soma + row) & 1)) return true;
	return true;
}


bool dfs(int steps, int pos, char mov) {
	int myPos = pos+1;
	if (mov == 'U') myPos = pos - 4;
	else if (mov == 'L') myPos = pos - 1;
	else if (mov == 'D') myPos = pos + 4;
	swap(grid[pos], grid[myPos]);
	result[steps] = mov;
	if (proc[grid] || !temSolucao())  {
		swap(grid[pos], grid[myPos]);
		return false;	
	}
	proc[grid] = true;
	int dist = mDist();

	if (!dist) {
		maxSteps = steps;
		return true;	
	}
	
	if (steps + dist > 45) {
		swap(grid[pos], grid[myPos]);
		return false;	
	}
	if (myPos + 1 < 16 && (myPos+1) % 4) {
		if (dfs(steps+1, myPos, 'R'))
			return true;	
	}
	if (myPos - 4 >= 0) {
		if (dfs(steps+1, myPos, 'U'))
			return true;	
	}
	if (myPos - 1 >= 0 && myPos % 4) {
		if (dfs(steps+1, myPos, 'L'))
			return true;	
	}
	if (myPos + 4 < 16) {
		if (dfs(steps+1, myPos, 'D'))
			return true;	
	}
	swap(grid[pos], grid[myPos]);
	return false;	
}

int main() {
	long s=  clock();
	scanf("%d", &N);
	int pos;
	for (int i = 0; i < N; i++) {
		for (int i = 0; i < 16; i++) {
			scanf("%d", &grid[i]);
			if (!grid[i])
				pos = i;
		}
		proc.clear();
		bool found = false;
		if (pos + 1 < 16 && (pos+1) % 4) {
			if (dfs(0, pos, 'R'))
				found = true;	
		}
		if (!found && pos - 4 >= 0) {
			if (dfs(0, pos, 'U'))
				found = true;	
		}
		if (!found && pos - 1 >= 0 && pos % 4) {
			if (dfs(0, pos, 'L'))
				found = true;	
		}
		if (!found && pos + 4 < 16) {
			if (dfs(0, pos, 'D'))
				found = true;	
		}
		if (!found) {
			printf("This puzzle is not solvable.\n");
			continue;
		}
		for (int i = 0; i< 4; i++) {
		for (int k = 0; k < 4; k++)
			cout << grid[i*4+k] << " ";
		cout << endl;
		}
		for (int i = 0; i <= maxSteps; i++) {
			putchar(result[i]);			
		}			
		putchar('\n');	
	}
	cout << (double)(clock()-s) / (double)CLOCKS_PER_SEC << endl;
	return 0;
}
