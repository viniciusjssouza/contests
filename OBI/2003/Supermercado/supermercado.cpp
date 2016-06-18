#include<cstdio>
#include<algorithm>

using namespace std;

int X[1010], Y[1010];

int main() {
	int N, tcase = 1;
	while(1) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &X[i], &Y[i]);
		}
		sort(X, X+N);
		sort(Y, Y+N);
		int meio = N / 2;
		if (N % 2) {
			printf("Teste %d\n%d %d\n\n", tcase++, X[meio], Y[meio]);	
		} else {
			printf("Teste %d\n%d %d\n\n", tcase++, (X[meio]+X[meio-1])/2, (Y[meio]+Y[meio-1])/2);	
		}
	}
	return 0;
} 
