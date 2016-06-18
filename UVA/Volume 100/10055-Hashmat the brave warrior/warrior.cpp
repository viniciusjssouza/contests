#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>

#define para(i,I,N) for(i = I; i < N; i++)

using namespace std;


int main() {
	long long int a,b;
	while(!feof(stdin) && scanf("%lld %lld", &a, &b) == 2) {
		printf("%lld\n", abs(a-b));
	}
	return 0;
}
