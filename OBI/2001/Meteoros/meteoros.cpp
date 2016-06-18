#include<cstdio>
#include<iostream>

using namespace std;

struct point {
	int x,y;
};

int main() {
	int N, tcase=1;
	point sup, inf;
	while(1) {
		scanf("%d %d %d %d", &sup.x, &sup.y, &inf.x, &inf.y);
		if (sup.x == 0 && sup.y == 0 && inf.x == 0 && inf.y == 0)
			break;
		scanf("%d", &N);
		int conta = 0;
		point queda;
		for (int i = 0;i < N; i++) {
			scanf("%d %d", &queda.x, &queda.y);
			if (queda.x >= sup.x && queda.x <= inf.x && queda.y <= sup.y &&
					queda.y >= inf.y)
				conta++;
		}
		printf("Teste %d\n%d\n\n", tcase++, conta);
	}
	return 0;
} 
