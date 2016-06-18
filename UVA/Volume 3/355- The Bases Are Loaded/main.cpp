/**********************************************
 Este arquivo esta atualmente modificado para a questao 389-Basically Speaking. 
  Com poucas modificacoes, pode ser utilizada na 355-The Bases Are Loaded.
 ***********************************************/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <stack>

#define CHAR_PARSER  55
#define STRLENGHT 	100000
using namespace std;

void removeIlegalChars(string &s);
unsigned long long getDecimalValue(string num, int base);
string getOutput(long long decValue, string num, int newBase);
bool isValidBaseNumber(string num, int base);
unsigned long long pow(unsigned long long base, unsigned long long exp);

int main()
{
	char in[8];
	int currBase, newBase;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while (scanf(" %s %d %d", in, &currBase, &newBase) == 3)
	{
		string num = in;
		unsigned long long currValue = getDecimalValue(num, currBase);
		string s = getOutput(currValue, num, newBase);
		if (s.length() > 7) cout << setw(7) << "ERROR" << endl;
		else
			cout << setw(7) << s << endl;		
	}
	return 0;	
}

void removeIlegalChars(string &s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ( (s[i] >= 'A' && s[i] <= 'F') || isdigit(s[i]) || (!i && s[i] == '-'));
		else
		{
			s = s.erase(i, 1);
			i--;
		}
	}
}

unsigned long long getDecimalValue(string num, int base)
{
	unsigned long long valor = 0; 
	unsigned long long expoente = 0;
	
	for (int i = num.length()-1; i >= 0; i--, expoente++)
	{	
		long long x = 0;
		if (isdigit(num[i]))
			x = num[i] - '0';
		else if (num[i] >= 'A' && num[i] <= 'F')
			x = num[i] - 'A' + 10;
		else x = 0;
		valor += x * pow(base, expoente);
	}
	return valor;
}

string getOutput(long long decValue, string num, int newBase)
{
	// algoritmo de troca de bases
	string newNum = "";
	stack<string> pilha;
	
	if (decValue < newBase)
	{
		char s[STRLENGHT];
		sprintf(s, "%llu", decValue);
		newNum += s;	
		return newNum;
	}
	while (decValue >= newBase)
	{
		unsigned long long rem = decValue % newBase;
		decValue = (long long)(decValue / newBase);
		string digit = "";
		char sup[STRLENGHT];

		if (rem < 10)
			sprintf(sup ,"%llu", rem);
		else
		{
			char x = rem + CHAR_PARSER;
			sprintf(sup ,"%c", x);
		}
		digit += sup;
		pilha.push(digit);
		
		if (decValue < newBase && decValue >= 0)
		{			
			digit = "";
			char sup2[STRLENGHT];
			if (decValue < 10)
				sprintf(sup2 ,"%llu", decValue);
			else
			{
				char x = decValue + CHAR_PARSER;
				sprintf(sup2 ,"%c", x);
			}
			digit += sup2;
			pilha.push(digit);
		}
	}
	while (!pilha.empty())
	{
		newNum += pilha.top();
		pilha.pop();
	}
	return newNum;	
}

bool isValidBaseNumber(string num, int base)
{
	int x = 0;
	for (int i = 0; i < num.length(); i++)
	{
		const char* digit = (num.substr(i, 1)).c_str();
		if (isdigit(digit[0]))
			x = atoi(digit);
		else
			x = digit[0] - CHAR_PARSER; 
		if (x >= base) return false;
	}
	return true;
}

unsigned long long pow(unsigned long long base, unsigned long long exp)
{
	unsigned long long result = 1;
	if (exp == 0) return 1;
	for (int i = 0; i < exp; i++)
		result *= base;
	 return result;
}

