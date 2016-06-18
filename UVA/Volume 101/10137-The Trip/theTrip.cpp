/******************************************************************
 *  UVa Problem - 10137 - The Trip -Programming Challenges
 *  Autor: Vinicius J. S. Souza
 *  Data: 17/01/2008
 * ****************************************************************/

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

double arredonda(double num, int precisao)
{
	double fatorPrecisao = pow(10.0, (double)precisao);
	double x = ( num * fatorPrecisao)+ 0.5;
	x = floor(x);
	return (x / fatorPrecisao);
}


int main()
{
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (true)
	{
		unsigned int n = 0;
		scanf("%d", &n);
		if (!n) return 0;
		
		double somaSup=0, somaInf=0, media=0, result = 0;
		double gasto = 0.0;
		vector<double> estudantes;
		for (unsigned int i= 0; i < n; i++)
		{
			double input = 0.0;
			scanf("%lf", &input);
			gasto = gasto+input;
			estudantes.push_back(input);
		}
		media = arredonda((gasto / n), 2);
	    	
		for (int i =0; i < n; i++)
		{
			if (estudantes[i] < media)
				somaInf += (media - estudantes[i]);
			else
				somaSup += (estudantes[i] - media);			
		}
		if (!somaInf)
			somaInf = somaSup;
		if (!somaSup)
			somaSup = somaInf;
		if (somaInf <= somaSup)
			result = somaInf;
		else
			result = somaSup;
		printf("$%.2lf\n", result);
	}
}
