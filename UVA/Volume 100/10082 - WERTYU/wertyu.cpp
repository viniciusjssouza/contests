/*************************************************************
 * UVa - 10082 - WERTYU - Livro Programming Challenges
 * 
 * Autor:Vinicius J. S. Souza
 * Data :09/07/2008 
 *************************************************************/
#include <iostream>
#include <cstdio>
#include <string>
#include <map>

using namespace std;

map<char,char> mapa;

void initMapa();

int main()
{
	initMapa();
	//freopen("input.txt", "r", stdin);
	while (true)
	{
		if (feof(stdin)) break;
		string line, decoded;
		getline(cin, line);
		if (line == "") break;
		decoded = line;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ') decoded[i] = ' ';
			else decoded[i] = mapa[line[i]];
		}
		cout << decoded << "\n";
	}
	return 0;
}

void initMapa()
{
	mapa['1'] = '`';
	mapa['2'] = '1';
	mapa['3'] = '2';
	mapa['4'] = '3';
	mapa['5'] = '4';
	mapa['6'] = '5';
	mapa['7'] = '6';
	mapa['8'] = '7';	
	mapa['9'] = '8';
	mapa['0'] = '9';
	mapa['-'] = '0';
	mapa['='] = '-';
	mapa['W'] = 'Q';
	mapa['E'] = 'W';
	mapa['R'] = 'E';
	mapa['T'] = 'R';
	mapa['Y'] = 'T';
	mapa['U'] = 'Y';
	mapa['I'] = 'U';
	mapa['O'] = 'I';
	mapa['P'] = 'O';
	mapa['['] = 'P';
	mapa[']'] = '[';
	mapa['\\'] = ']';
	mapa['S'] = 'A';
	mapa['D'] = 'S';
	mapa['F'] = 'D';
	mapa['G'] = 'F';
	mapa['H'] = 'G';
	mapa['J'] = 'H';
	mapa['K'] = 'J';
	mapa['L'] = 'K';
	mapa[';'] = 'L';
	mapa['\''] = ';';
	mapa['X'] = 'Z';
	mapa['C'] = 'X';
	mapa['V'] = 'C';
	mapa['B'] = 'V';
	mapa['N'] = 'B';
	mapa['M'] = 'N';
	mapa[','] = 'M';
	mapa['.'] = ',';
	mapa['/'] = '.';
}
