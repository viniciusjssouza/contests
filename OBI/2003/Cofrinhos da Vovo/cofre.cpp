 #include<cstdio>

using namespace std;

int main() {
	int tcase = 1;
	while(1) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		int total = 0;
		printf("Teste %d\n", tcase++);
		for (int i= 0; i <N; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			total += (x-y);
			printf("%d\n", total);	
		}
		putchar('\n');
	}	
	return 0;
}


