#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class BadNeighbors
{
public:
	BadNeighbors()
	{}

	int maxDonations(vector<int> &donations)
	{
		if (donations.size() == 2)
			return max(donations[0], donations[1]);
		vector<int> tabela(donations.size());	
		tabela[0] = donations[0];
		tabela[1] = donations[1];
		for (int i = 2; i < donations.size(); i++)
		{
			if (i == donations.size()-1)
				tabela[i] = max(tabela[i-1], tabela[i-2]-donations[0] + donations[i]);
			else
				tabela[i] = max(tabela[i-1], tabela[i-2]+donations[i]);
		} 
		return tabela[donations.size()-1];
	}
};
