#include<cstdio>

using namespace std;

int N, tcase = 1;

int main() {
	while (1) {
		scanf("%d", &N);
		if (!N)
			break;
		int venc = -1, x;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			if (x == i) {
				venc = x;
			}
		}
		printf("Teste %d\n%d\n\n", tcase++, venc);
	}
}
