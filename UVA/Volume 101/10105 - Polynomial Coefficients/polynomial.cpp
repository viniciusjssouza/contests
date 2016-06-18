#include<iostream>
#include<deque>

#define MAXN 13

using namespace std;

long long bc[MAXN][MAXN];

void getCoeficientes()
{
	long long i,j;
	for (i=0; i< MAXN; i++) 
		bc[i][0] = 1;
	for (j=0; j< MAXN; j++) 
		bc[j][j] = 1;
	for (i=1; i< MAXN; i++)
		for (j=1; j<i; j++)
			bc[i][j] = bc[i-1][j-1] + bc[i-1][j];	
}

int main()
{
	getCoeficientes();
	while (true)
	{
		if (feof(stdin)) break;
		deque<long long> exp;
		long long n, k, aux;
		cin >> n >> k;		
		if (feof(stdin)) break;
		for (int i = 0; i < k; i++)
		{
			cin >> aux;
			if (aux)
				exp.push_back(aux);				
		}

		long long coef = 1;
		int pos  = 0;		
		for(int nVar = exp.size(); nVar > 2; n-= exp[pos], nVar--, pos++)
		{
			coef *= bc[n][exp[pos]];
			//cout << "bc: " << bc[n][exp[pos]] << endl;
		}
		coef *= bc[n][exp[pos]];
		//cout << "bc: " << n << endl;		
		cout << coef << endl;
	}	
	return 0;
}
