/*************************************************************************************************
 * UVa - 120 -Stacks of Flapjacks - Livro Programming Challenges 
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 20/08/08 
 ***************************************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<int> pilha(100);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	while (!feof(stdin))
	{
		string line;
		getline(cin, line);
		
		istringstream is(line);
		int conta =0;
		while (is >> pilha[conta])
			conta++;
		vector<int> copy(pilha.begin(), pilha.begin() + conta);
				
		sort(copy.begin(), copy.begin() + conta);
		/*
		for (int i = 0; i < conta; i++)
					cout << "Cpy:" << copy[i] << endl;
		*/		
		cout << line << endl;
		bool troca = false;
		for (int i = conta-1; i >= 0; i--)
		{
			int max = copy[i];
			if (pilha[i] != max)
			{
				troca = true;
				if (i != (conta-1)) cout << ' ';
				vector<int>::iterator location = find(pilha.begin(), pilha.begin() + i + 1, max);
				if (location != pilha.begin())
				{	
					//cout << "Entrei:" << endl;//<< pilha[i] << " " << max << endl;
					cout << (conta - (location - pilha.begin())) << ' ';
					reverse(pilha.begin(), (location+1));
				}
				cout << (conta - i);
				reverse(pilha.begin(), pilha.begin() + i + 1);
			}
		}
		if (troca)
			cout << ' ';
		cout << "0\n";
	}
	return 0;
}