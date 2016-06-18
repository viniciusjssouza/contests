/********************************************************************
 * UVa - Problema 848 - Fmt - Livro Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 06/08/2008
 *******************************************************************/

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

#define debug true
#define MAX	  72

using namespace std;

void doFmt();
bool preencheAcima(int tam, int pos, string &result);
void preencheAbaixo(int pos, string &result);

vector<string> input;
/*0
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	string line = "";
	while(!feof(stdin))
	{		
		getline(cin, line);
		int i = line.size() - 1;
		
		for (; i >= 0 && line[i] == ' '; i--);
		line.erase(i+1, line.size() - i);	
		
		//if (debug) cout << "Input sem espacos:" << line << endl;
		
		input.push_back(line);
	}
	doFmt();

	return 0; 
}
*/


void doFmt()
{
	for (int i = 0; i < input.size(); i++)
	{
		//if (debug) cout << "str:" << str << endl;
		if (input[i] == "" || input[i].size() == MAX); 
	
		else if (input[i].size() < MAX)
		{
			if ((i+1) >= input.size() || input[i+1] == "" || input[i+1][0] == ' ');
			else
			{
				string aux = "";
				if (preencheAcima(MAX-input[i].size()-1, i+1, aux))
					input[i] += ' ' + aux;
				//if (debug) cout << "\nstr:" << aux << endl;  
			}
		}
		
		else
		{
			if (input[i].find(" ") != string::npos)
			{
				string aux = "";
				preencheAbaixo(i, aux);
				vector<string>::iterator ite = input.begin() + i + 1;
				input.insert(ite, aux);				
			}
		}

		int k = input[i].size() - 1;
		for (; k >= 0 && input[i][k] == ' '; k--);
		input[i].erase(k+1, input[i].size()- k);
		
		cout << input[i];
		if ((i+1) < input.size()) cout << endl;
	}
}

bool preencheAcima(int tam, int pos, string &result)
{
	result = "";
	bool alterado = false;
	while (true)
	{
		//cout << "\nresult:" << result << " pos:" << pos<< endl;
		if ((input[pos].size() <= tam) && input[pos] != "")
		{
			string aux = input[pos].substr(0, input[pos].size());
			tam -= aux.size();
			if (tam > 0)
			{
				tam--;
				aux += ' ';
			}
			result += aux;
			vector<string>::iterator ite = input.begin() + pos;
			input.erase(ite);
			alterado = true;	
			continue;
		}		
		else
		{
			for (int i = tam; i >= 0; i--)
			{
				if (input[pos][i] == ' ')
				{
					//if (debug) cout << "i = " << i << " size=" << str.size() << endl;
					result += input[pos].substr(0, i);
					input[pos].erase(0, i+1);
					return true;
				}
			}
			return alterado;
		}
		pos++;
		result += ' ';
	}
	return alterado;
}

void preencheAbaixo(int pos, string &result)
{
	int space = input[pos].find(" ");
	if (space >= MAX)
	{
		result = input[pos].substr(space+1, input[pos].size()-space);
		input[pos].erase(space, input[pos].size()-space+1);
		return;
	}
	else 
	{
		for (int i = MAX; i >= 0; i--)
		{
			if (input[pos][i] == ' ')
			{
				result = input[pos].substr(i+1, input[pos].size()-i);
				input[pos].erase(i, input[pos].size()-i + 1);
				return;
			}
		}
	}
}