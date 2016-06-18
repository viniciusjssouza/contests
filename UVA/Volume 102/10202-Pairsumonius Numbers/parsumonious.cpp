#include<iostream>
#include<set>
#include<deque>
#include<map>
#include<vector>

using namespace std;

int n;


bool getPairs(long long a0, deque<long long> &a, multiset<long long> p)
{
	a.clear();
	a.push_front(a0);
	vector< vector<bool> > removed(n);
	for (int i = 0; i < n; i++)
		removed[i] = vector<bool>(n, false);

	while (p.size())
	{
		multiset<long long>::iterator ite;
		for (int i = 1; i < a.size()-1; i++)
		{
			for (int k = i+1; k < a.size(); k++)
			{
				if (removed[i][k]) continue;
				ite = p.find(a[i]+a[k]);
				if (ite != p.end())
				{
					//if (a0 == 111) cout << *ite << endl;
					p.erase(ite);
					removed[i][k] = true;
				}
				else
					return false;
			}
		}		
		if (!p.size()) break;	
		long long nextElement = (*(p.begin())) - a0;
		a.push_back(nextElement);
		removed[0][a.size()-1] = true;
		//if (a0 == 1) cout << *p.begin()<< "-" << a0 << endl << endl;	
		p.erase(p.begin());	
	}
	return true;
}

int main()
{
	while (cin >> n && !feof(stdin))
	{
		multiset<long long> p;
		deque<long long> a;
		int nIn = (n * (n-1)) / 2;
		for (int i = 0; i < nIn; i++)
		{
			long long foo;
			cin >> foo;
			p.insert(foo);	
		}
		long long a0 = *p.begin()/2;
		
		if (a0 < 0)
		{
			for(; !getPairs(a0, a, p) && a0 <= 0; a0++);
			if (a0 > 0) 
			{
				cout << "Impossible\n";		
				continue;
			}
		}
		else
		{	
			for(; !getPairs(a0, a, p) && a0 >= 0; a0--);
			if (a0 < 0) 
			{
				cout << "Impossible\n";		
				continue;
			}
		}
		

		for (int i = 0; i < a.size(); i++)
		{
			if (i) putchar(' ');
			cout << a[i];				
		}
		putchar('\n');
	}
	return 0;
}
