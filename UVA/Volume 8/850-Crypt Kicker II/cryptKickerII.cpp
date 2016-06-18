/*******************************************************************
 * UVa - Problema 850 - Crypt Kicker II - Programming Challenges
 *  
 * Autor: Vinicius J. S. Souza
 * Data : 14/07/2008
 ********************************************************************/

#include <iostream>
#include <string>
#include <cstdio>
#include <map>
#include <vector>

#define 	debug		false	
#define 	TAM			128
#define 	NULL_CHAR	'?'
using namespace std;

const string TEXT = "the quick brown fox jumps over the lazy dog";
const string NO = "No solution.";

bool montaDicionario(const string &in, vector<char> &dicionario);
string decrypt(const string &line, const vector<char> &dicionario);
void replaceAll(string &str, char atual, char novo, int start, vector<bool> &replaced);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int numCases = 0;
	cin >> numCases;
	getchar();	getchar();
	bool isInicio = true;
	
	for (int i = 0; i < numCases; i++)
	{
		vector<char> dicionario(TAM, NULL_CHAR);
		vector<string> in;		
		string line;
		
		if (!isInicio) cout << endl;
		else isInicio = false;
		
		bool noSolution = true;
		while (true)
		{
			if (feof(stdin)) break;
			getline(cin, line);
			if (line == "") break;
			if (montaDicionario(line, dicionario)) 
				noSolution =false;
			in.push_back(line);
		}
		if (noSolution)
			cout << NO << endl;
		else	
		{
			for (int k = 0; k < in.size(); k++)
				cout << decrypt(in[k], dicionario) << endl;
		}
	}
	return 0;
}

bool montaDicionario(const string &in, vector<char> &dicionario)
{
	if (in.size() != TEXT.size()) return false;
	string aux = in;
	vector<char> temp(TAM, NULL_CHAR);				
	vector<bool> replaced(aux.size(), false);
	
	for (int k = 0; k < TEXT.size(); k++)
	{	
		if (in[k] == ' ' && TEXT[k] != ' ') return false; 
		if (temp[aux[k]] == NULL_CHAR && !replaced[k])
		{	
			temp[aux[k]] = TEXT[k];
			replaceAll(aux, aux[k], TEXT[k], k, replaced);				
		}
	}
	if (aux == TEXT)
	{
		dicionario = temp;
		return true;
	}
	return false;
}

void replaceAll(string &str, char atual, char novo, int start, vector<bool> &replaced)
{
	for (int i = start; i < str.size(); i++)
	{
		if (str[i] == atual && !replaced[i])
		{
			str[i] = novo;
			replaced[i] = true;
		}
	}
}

string decrypt(const string &line, const vector<char> &dicionario)
{
	string result = line;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')
			result[i] = dicionario[line[i]];
	}
	return result;
}
