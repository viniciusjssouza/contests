#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>

using namespace std;

int main() {
	long long n;
	int tcase=1;
	while(1) {
		scanf("%lld", &n);
		if (n < 0) break;
		long long int r = (1 << n) + 1;
		r *= r;
		printf("Teste %d\n%lld\n\n", tcase++, r);
	}
}
 
