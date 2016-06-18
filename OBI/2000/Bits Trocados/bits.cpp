#include<cstdio>

using namespace std;

int main() {
	int tcase = 1, N;
	while (true) { 
		scanf("%d", &N);
		if (!N) 
			break;
		int n50 = N / 50;
		N = N % 50;
		int n10 = N / 10;
		N = N % 10;
		int n5 = N / 5;
		N = N % 5;
		int n1 = N;
		printf("Teste %d\n%d %d %d %d\n\n", tcase++, n50, n10, n5, n1);
	}
} 
