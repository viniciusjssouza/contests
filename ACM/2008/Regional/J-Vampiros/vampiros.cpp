/*********************************************************************************
* UVa 11499 - Vampiros - Maratona Regional 2008
*
* Autor: Vinicius J. S. Souza
* Data: 11/08/2009
* Tecnicas utilizadas: resolucao de sistemas lineares por substituicao 
*****************************************************************************/

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int main()
{
	while (true)
	{
		int ev1, ev2, at, d;
		scanf("%d %d %d %d", &ev1, &ev2, &at, &d);
		if (!ev1 && !ev2 && !at && !d)
			break;
		int n = ev1+ev2;
		//reducao para o caso d=1;
		if (d != 1)
		{
			int sup = (int) ceil( (double)(n-ev1) / (double)d );
			int inf = (int) ceil( (double)(ev1) / (double)d );
			n = sup + inf;
			ev1 = inf;
		}
		vector<double> result(n+1, -1.0);
		vector<double> coef(n+1);
		double b = (double)at /  (double)6.0;
		double a = 1.0 - b;
		result[0] = 0.0;
		result[n] = 1.0;
		coef[0] = 0.0;

		//calculo dos coeficientes da formula: coef(i) = b / (1 - a * coef(i-1)) 
		for (int i = 1; i < n; i++)
			coef[i] = b / (1-a*coef[i-1]);
		// calculo das propabilidades: P(i) = coef(i) * P(i+1)
		for (int i = n-1; i >= 0 && i >= ev1; i--)
			result[i] = coef[i] * result[i+1];
		printf("%.1f\n", (result[ev1]*100.0));
		
	}
	return 0;
}
