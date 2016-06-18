#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long int64;

#define phi 1.618033989

int64 solve(int inf, int sup, int b)
{
	if (sup < inf)
		return 0;
	int64 limit = (int64)ceil((double)phi * (double)b);
	if (limit < inf)
		limit = inf; 
	int64 sol = (sup - limit + 1); 
	return (sol > 0 ? sol : 0);
}

int a1, a2, b1, b2, T;

int main()
{
	scanf("%d", &T);
	for (int tcase = 1; tcase <= T; tcase++) {
		scanf("%d %d %d %d", &a1, &a2, &b1, &b2);
		int64 sol = 0;
		for (int b = b1; b <= b2; b++) {
			
			sol += solve(a1, a2, b);
		}
		for (int a = a1; a <= a2; a++) {
			sol += solve(b1, b2, a);
		}
		printf("Case #%d: %lld\n", tcase, sol);
	}
	return 0;
}
 
