#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	long double n;
	while (1)
	{
		cin >> n;
		if (!n) break;
		long double result = floor(sqrt(n));
		if ((result * result) == n)
			cout << "yes\n";
		else
			cout << "no\n";		
	}
	return 0;
}
