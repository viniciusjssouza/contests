#include<iostream>
#include<set>

using namespace std;

int main()
{
//	freopen("in.txt", "r", stdin);
	int d, a;
	while (1)
	{
		cin >> a >> d;
		if (!a && !d) break;
		multiset<int> defensores;
		int atacantePos = 10000000;
		for (int i = 0 ;i < a; i++)
		{
			int x;
			cin >> x;
			if (x < atacantePos)
				atacantePos = x;
		}
		for (int i = 0; i < d; i++)
		{
			int foo;
			cin >> foo;
			defensores.insert(foo);
		}
		multiset<int>::iterator ite = defensores.begin();
		ite++;
		if (atacantePos < *ite)
			cout << "Y\n";
		else
			cout << "N\n";
	}
	return 0;
}