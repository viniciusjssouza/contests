#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int getOpostoPos(int pos);
bool equals(int a[6], int b[6]);


int main()
{
	int nCubos;
	while (1)
	{
		cin >> nCubos;
		if (!nCubos) break;
		if (nCubos == 1)
		{
			cout << 1 << endl;
			continue;
		}
		
		int cubos[nCubos][6];
		for (int i = 0; i < nCubos; i++)
		{
			for (int k = 0; k < 6; k++)
				cin >> cubos[i][k];
		}

		vector<bool> iguais(nCubos, false);
		int conta = 0;
		for (int i = 0; i < nCubos; i++)
		{
			if (iguais[i])
				continue;
			for (int k = i+1; k < nCubos; k++)
			{
				if (equals(cubos[i], cubos[k]))
				{					
					if (!iguais[k])
					{
						iguais[k] = true;
						if (!iguais[i])
						{
							conta++;
							iguais[i] = true;
						}
					}
				}
			}
		}

		for (int i=0; i < iguais.size(); i++)
		{
			if (!iguais[i])
				conta ++;
		}
		cout << conta << endl;
	}
	return 0;
}

int getOpostoPos(int pos)
{
	switch(pos)
	{
		case 0: return 5;
		case 1: return 3;
		case 2: return 4;
		case 3: return 1;
		case 4: return 2;
		case 5: return 0;
	}
	return 0;
}

bool equals(int a[6], int b[6])
{
	bool found = false;
	int k = 0;
	for (; k < 6; k++)
	{
		if (a[0] == b[k] && a[getOpostoPos(0)] == b[getOpostoPos(k)])
		{
			found = true;
			break;
		}
	}
	if (!found) return false;
	
	switch(k)
	{
		case 0: break;
		case 1: swap(b[1], b[0]);
				swap(b[1], b[3]);
				swap(b[1], b[5]);
				break;
		case 2: swap(b[2], b[0]);
				swap(b[2], b[4]);
				swap(b[2], b[5]);
				break;
		case 3: swap(b[3], b[0]);
				swap(b[3], b[1]);
				swap(b[3], b[5]);
				break;
		case 4: swap(b[4], b[0]);
				swap(b[4], b[2]);
				swap(b[4], b[5]);
				break;
		case 5: swap(b[0], b[5]);
				swap(b[4], b[2]);
				break;
	}	
	
	for (int conta = 0; conta < 4; conta++)
	{
		bool equal = true;
		for (int i = 1; i < 5; i++)
		{
			if (a[i] != b[i])
			{
				equal = false;
				break;
			}
		}
		if (equal) return true;
		swap(b[1], b[2]);
		swap(b[1], b[3]);
		swap(b[1], b[4]);
	}
	return false;
}
