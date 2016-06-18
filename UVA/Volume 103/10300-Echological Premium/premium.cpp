#include<iostream>
#include<cstdio>

using namespace std;

int N, F;
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d",&F);
		unsigned long long int soma = 0;
		for (int k = 0; k < F; k++) {
			unsigned long long x,y,z;
			scanf("%llu %llu %llu", &x, &y, &z);
			//cin >> x >> y >> z;
			soma += (x*z);
		}
		printf("%llu\n", soma);
	}
	return 0;
}