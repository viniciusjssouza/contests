/*******************************************************************************
* Feynman - Final Sul-Americana 2008
*
* Autor: Vinicius J. S. Souza
* Data: 02/09/2009
* Tecnicas: Programacao dinamica simples
*********************************************************************************/
#include<iostream>

using namespace std;

int main()
{
	unsigned long long dp[101];
	dp[1]= 1;
	for (unsigned long long i = 2; i <= 100; i++)
		dp[i] = (i*i + dp[i-1]);

	while (true)
	{
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		cout << dp[n] << endl;
	}	
	return 0;
}
