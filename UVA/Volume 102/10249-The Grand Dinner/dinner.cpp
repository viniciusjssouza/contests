#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

int nTimes = 0, nMesas = 0;

struct Time
{
	int nMembros;
	int id;
};

void printVetores(vector<Time> &times, vector<int> &mesas)
{
	for (int i = 0; i < times.size(); i++)
	{
		cout << "Time:" << times[i].id << "   nMembros:" << times[i].nMembros << endl;
	} 
	for (int i = 0; i < mesas.size(); i++)
	{
		cout << "Mesa: " << i << "  Capacidade:" << mesas[i] << endl;
	}
}

bool compareByNMembros(Time t1, Time t2)
{
	if (t1.nMembros >= t2.nMembros)
		return true;
	return false;
}

bool distribuiTimes(vector<Time> &times, vector<int> &mesas, vector<vector<int> > &path)
{
	for (int i = 0; i < times.size(); i++)
	{
		//printVetores(times, mesas);
		int k = 0;
		int m = 0;
		while (k < mesas.size() && m < times[i].nMembros)
		{
			if (mesas[k] > 0)
			{
				mesas[k]--;
				m++;
				path[times[i].id].push_back(k+1); 
			}
			k++;
		}
		if (k >= nMesas && m < times[i].nMembros) return false;
	}
	return true;
}

int main()
{
	while (true)
	{
		cin >> nTimes >> nMesas;
		if (!nTimes && !nMesas)
			break;
		vector<int> mesas(nMesas);
		vector<Time> times(nTimes);
		for (int i = 0; i < times.size(); i++)
		{
			Time t;
			t.id = i;
			cin >> t.nMembros;
			times[i] = t;
		}
		for (int i = 0; i < mesas.size(); i++)
			cin >> mesas[i];
		sort(times.begin(), times.end(), compareByNMembros);

//		printVetores(times, mesas);

		vector< vector<int> > path(nTimes, vector<int>());
		if (!distribuiTimes(times, mesas, path))
			printf("0\n");
		else
		{
			printf("1\n");
			
			for (int i = 0; i < path.size(); i++)
			{
				for (int k = 0; k < path[i].size(); k++)
				{
					if (k)
						putchar(' ');
					printf("%d", path[i][k]);
				}
				putchar('\n');
			}
		}
	}
	return 0;
}
