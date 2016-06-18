#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

#define 	CHAR_PARSER		55;

using namespace std;

string getResposta(string x, string y);
int getMinBase(string x);
unsigned long calcula(int base, string valor);

int main()
{
	char in1[1000], in2[1000];
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
		
	while (scanf(" %s %s", in1, in2) == 2)
		cout << getResposta(in1, in2) << endl;
	
	return 0;
	
}

string getResposta(string x, string y)
{
	string resposta = "";
	char b1[30];
	char b2[30];
		
	for (int base1 = getMinBase(x); base1 <= 36; base1++)
	{
		unsigned long num1 = calcula(base1, x);
		for (int base2 = getMinBase(y); base2 <= 36; base2++)
		{
			unsigned long num2 = calcula(base2, y);
			sprintf(b1, "%d", base1);
			sprintf(b2, "%d", base2);
			if (num1 == num2)
			{
				resposta = resposta + x + " (base " + b1 + ") = " + y + " (base " + b2 + ")";
				return resposta;
			}	
		}
	}
	resposta = resposta + x + " is not equal to " + y + " in any base 2..36";
	return resposta;
}

unsigned long calcula(int base, string valor)
{
	unsigned long expoente = 0;
	unsigned long resultado = 0;

	for (int i = valor.size()-1; i >= 0; i--)
	{
		if (isdigit(valor[i]))
		{
			string num = "";
			num = valor.substr(i, 1);
			unsigned long parte = atoi(num.c_str());
			resultado += (unsigned long)(parte * pow((double)base, (double)expoente));
			expoente ++;
		}
		else if (isalpha(valor[i]))
		{
			unsigned long parte = valor[i] - CHAR_PARSER;
			resultado += (unsigned long) (parte * pow((double)base, (double)expoente));
			expoente ++;
		}
	}	
	return resultado;
}

int getMinBase(string x)
{
	unsigned int base = 2;
	for (int i = x.length()-1; i >= 0; i--)
	{
		if (isdigit(x[i]))
		{
			int digit = x[i] -'0'; 
			if(digit >= base)
				base = digit + 1;		
		}
		else if (isalpha(x[i]))
		{
			int digit = x[i] - 'A' + 10; 
			if(digit >= base)
				base = digit + 1;
		}
	}
	return base;
}
