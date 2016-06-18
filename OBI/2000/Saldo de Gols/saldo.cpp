#include<cstdio>

using namespace std;

int data[10010], N, tcase = 1;
int main() {
	while (1) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			int x, y;
			scanf("%d %d", &x ,&y);
			data[i] = x - y;
		}
		int sz = 0x3fffffff, begin = -1, end= -1, max= 0;
		for (int i = 0; i < N; i++) {
			int soma = 0;
			for (int k = i; k < N; k++) {
				soma += data[k];
				if ((soma > max) || (soma == max && (k-i) > sz)) {
					begin = i;
					end = k;
					sz = k - i;
					max = soma;
				}
			}
		}
		if (max > 0)
			printf("Teste %d\n%d %d\n\n", tcase++, begin+1, end+1);
		else 
			printf("Teste %d\nnenhum\n\n", tcase++);
	}
	return 0;
}
