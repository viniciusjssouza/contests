/*******************************************************************************
* UVA 10131 - Is Bigger Smarter? - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 15/07/2009
* Tecnicas utilizadas: Programacao Dinamica + sorting
********************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Elefante
{
	int peso;
	int qi;
	int id;	
};

bool compareElefante(Elefante e1, Elefante e2)
{
	if (e1.peso < e2.peso)
		return true;
	return false;
}

void reconstroiCaminho(vector<Elefante> &input, vector<int> &path, int pos)
{
	if (pos == -1) return;
	reconstroiCaminho(input, path, path[pos]);
	printf("%d\n", input[pos].id);
}

void printInt(int v)
{
	printf("%d ", v);
}

int main()
{
	vector<Elefante> input;
	int peso, qi;
	int counter = 1;
	while (!feof(stdin) && scanf("%d %d", &peso, &qi) == 2)
	{
		Elefante el;
		el.id = counter;
		el.peso = peso;
		el.qi = qi;
		input.push_back(el);
		counter ++;
	}
	sort(input.begin(), input.end(), compareElefante);
/*	
	for (int i = 0; i < input.size(); i++)
	{
		cout << "Elefante: " << input[i].id << "  Peso:" << input[i].peso << " QI:" << input[i].qi;
		cout << endl;
	}
*/

	vector<int> path(input.size(), -1);
	vector<int> tabela(input.size(), 1);
	int ultimo = -1;
	int maxValue = -100000000;
	for (int i = 0; i < input.size(); i++)
	{
		for (int k = i-1; k >= 0; k--)
		{
			if (input[i].qi < input[k].qi && input[i].peso > input[k].peso)
			{
				if (tabela[k] +1 > tabela[i])
				{
					tabela[i] = tabela[k] + 1;			
					path[i] = k;				
				}
				if (tabela[i] > maxValue)
				{
					maxValue = tabela[i];
					ultimo = i;
				}
			}
		}
	}
/*
	printf("Path:"); 
	for_each(path.begin(), path.end(), printInt);
	putchar('\n');

	for (int i = 0; i < path.size(); i++)
		cout << tabela[i] << "  Id:" << input[i].id  << "  Path:" << path[i] << endl;
*/	
	cout << maxValue << endl;
	reconstroiCaminho(input, path, ultimo);

}

