/*******************************************************************
 * UVa - 10132 - File Fragmentation - Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 26/07/2008 
 ******************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define debug false

using namespace std;

void defrag(vector<string> &in, string &result);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int numCases = 0;
	cin >> numCases;
	getchar(); getchar();
	bool inicio = true;

	while (numCases--)
	{
		if (!inicio) cout << endl;
		else inicio = false;
	
		vector<string> in; 
		string line = "", result = "";
		while (true)
		{
			if (feof(stdin))break;
			getline(cin, line);			
			if (debug) cout << line << endl;			
			if (line == "") break;
			in.push_back(line);
		}
		defrag(in, result);
		cout << result << endl;
	}
	return 0;
}

void defrag(vector<string> &in, string &result)
{
	if (in.size() == 0) 
		return;
	vector<string> combinacoes;
	
	for (int i = 0; i < in.size(); i++)
	{
		for (int k = 0; k < in.size(); k++)
		{
			if (i == k) continue;
			combinacoes.push_back(in[i] + in[k]);
		}
	}
	
	if (debug)
	{
		cout << "Combinacoes:\n";
		for (int i = 0; i < combinacoes.size(); i++)
			cout << combinacoes[i] << endl;
	}
	
	int n = in.size() / 2;
	
	for (int i = 0; i < combinacoes.size(); i++)
	{
		string aux = combinacoes[i];
		int conta = 0;
		for (int k = 0; k < combinacoes.size(); k++)
		{
			if (combinacoes[i] == combinacoes[k])
				conta++;
		}
		
		if (conta >= n)
		{
			result = combinacoes[i];
			return;
		}
	}
}

