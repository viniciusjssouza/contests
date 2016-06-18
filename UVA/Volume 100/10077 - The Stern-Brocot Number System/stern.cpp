#include<iostream>
#include<string>

using namespace std;

struct Fracao
{
	long num;
	long den;
};

int main()
{
	long num, den;
	Fracao input;
	while (cin >> input.num >> input.den)
	{
		if (input.num == 1 && input.den == 1) break;
		string output = "";
	
		Fracao dir, esq, atual;
		esq.num = 0; 		esq.den = 1;
		dir.num = 1;    	dir.den = 0; 
		atual.num = 1; 		atual.den = 1;
		
		while(atual.num != input.num || atual.den != input.den)
		{
			double a = (double)atual.num / (double)atual.den;
			double i = (double)input.num / (double) input.den;
			if (i < a)
			{
				dir.num = atual.num;
				dir.den = atual.den;					
				atual.num += esq.num;
				atual.den += esq.den;				
				output += 'L';				
			}			
			else
			{
				esq.num = atual.num;
				esq.den = atual.den;					
				atual.num += dir.num;
				atual.den += dir.den;
				output += 'R';
			}
		}		
		cout << output << endl;
	}
	return 0;
}
