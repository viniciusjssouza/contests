#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstdlib> 
#include<cmath>
#include<map>

using namespace std;

int data[110];
int N;
bool used[10010];

int main() {
	int x,y, tcase = 1;
	while(1) {
		scanf("%d %d %d", &x, &y, &N);
		if (x == 0 && y == 0 && N == 0)
			break;
		int soma = 0;
		for	(int i = 0; i < N; i++) {
			scanf("%d", &data[i]);
			soma += data[i];
		}
		int dif = abs(x-y);
		int t = (soma - dif);
		if (t % 2) {
			printf("Teste %d\nN\n\n", tcase++);
			continue;
		}
		t /= 2;
		memset(used, 0, sizeof(used));
		int max= 0;
		used[0] = true;
		for (int i = 0; i < N && !used[t]; i++) {
			for (int k = max; k >= 0; k--) {
				if (used[k]) {
					used[data[i] + k] = true;
				}
			}	
			max += data[i];
		}	
		printf("Teste %d\n%c\n\n", tcase++, used[t] ? 'S':'N');
	}
	return 0;
} 
