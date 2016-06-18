/******************************************************************************
* UVa 11495 - Loop musical - Maratona - Regional 2008
*
* Autor: Vinicius J. S. Souza
* Data: 10/08/2009 
********************************************************************************/
#include<iostream>
#include<vector>

using namespace std;

int main()
{
	while (true)
	{
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		vector<int> onda(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &onda[i]);
		int last = n-1;
		register int conta = 0;
		if (n == 1)
			conta++;
		else if (onda[0] > onda[last] && onda[0] > onda[1])
			conta++;
		else if (onda[0] < onda[last] && onda[0] < onda[1])
			conta++;
		for (register int i = 1; i < last; i++)
		{			
			if (onda[i] > onda[i-1] && onda[i] > onda[i+1])
				conta++;
			else if (onda[i] < onda[i-1] && onda[i] < onda[i+1])
				conta++;
		}
		if (onda[last] > onda[0] && onda[last] > onda[last-1])
			conta++;
		else if (onda[last] < onda[0] && onda[last] < onda[last-1])
			conta++;
		printf("%d\n", conta); 
	}
	return 0;
}
