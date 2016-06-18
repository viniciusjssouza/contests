#include<iostream>
#include<cstdlib>

using namespace std;

int main()
{
	while (true)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (!x1 && !y1 && !x2 && !y2)
			break;
		int result;
		if (x1 == x2 && y1 == y2)
			result = 0;
		else if (x1 == x2 || y1 == y2)
			result = 1;
		else if ( abs(x2-x1) == abs(y2-y1) )
			result = 1;
		else
			result = 2;
		printf("%d\n", result);
	}
	return 0;
}
