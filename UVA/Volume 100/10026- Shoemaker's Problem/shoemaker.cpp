#include<iostream>
#include<set>

using namespace std;

struct Order
{
	int t;
	int c;
	int id;	

};

struct Compare
{
	bool operator()(const Order &a, const Order &b)
	{
		double razao1 = ((double)a.c / (double)a.t);
		double razao2 = ((double)b.c / (double)b.t);
		//cout << razao1 << ".." << razao2 << endl;
		if (razao1 > razao2)
			return true;		
		else if (razao2 > razao1)
			return false;
		else
		{
		
			char sA[100];
			char sB[100];
			sprintf(sA, "%d", a.id);
			sprintf(sB, "%d", b.id);
			string strA = sA;
			string strB = sB;
			
			if (a.id < b.id)
				return true;
			else
				return false;
		}
	}
};


int main()
{
	//freopen("in.txt", "r", stdin);
	
	int nTest;
	cin >> nTest;
	for (int t = 0; t < nTest; t++)
	{
		int n;
		if (t) putchar('\n');
		multiset<Order, Compare> input;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			Order o;						
			cin >> o.t >> o.c;
			o.id = (i+1);
			input.insert(o);
		}
		for (multiset<Order>::iterator ite = input.begin(); ite != input.end(); ite++)
		{
			if (ite != input.begin()) cout << ' ';
			cout << (*ite).id;			
		}
		cout << endl;
	}
	return 0;
}
