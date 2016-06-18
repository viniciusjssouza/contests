/***********************************************************************************
* UVA 10154 - Weights and Measures - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 23/07/2009
* Tecnicas: dp bidirecional + sorting 
**********************************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>

#define MAX	1000000000

using namespace std;

struct Turtle
{
	unsigned long long weight;
	unsigned long long strength;	
};

bool compare(Turtle t1, Turtle t2)
{
	if (t1.strength < t2.strength)
		return true;
	else if (t1.strength > t2.strength)
		return false;
	else if (t1.weight < t2.weight)
		return true;
	return false;
}

int main()
{
	vector<Turtle> data;
	string line = "";
	while (getline(cin, line) && line != "")
	{
		stringstream buffer(line);			
		Turtle t;
		buffer >> t.weight >> t.strength;
		data.push_back(t);
	}
	sort(data.begin(), data.end(), compare);
	int size = data.size();
	vector<vector<unsigned long long> > tabela(size, vector<unsigned long long>(size,MAX));
	
	for (int i = 0; i < size; i++)
		tabela[0][i] = data[i].weight;

	int max;	

	for (int i = 1; i < size; i++)
	{
		for (int k = i; k < size; k++)
		{
			if (tabela[i-1][k-1]+data[k].weight <= data[k].strength)
			{
				tabela[i][k] = min(tabela[i][k-1], tabela[i-1][k-1]+data[k].weight);
			}
			else
				tabela[i][k] = tabela[i][k-1];				
		}
		if (tabela[i][size-1] == MAX)
		{
			max = i;
			break;
		} 
	}
	cout << max << endl;
	return 0;
}
