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
	int v,t;
	while(scanf("%d %d", &v, &t) == 2) {
		printf("%d\n", 2*v*t);
	}
	return 0;
}
