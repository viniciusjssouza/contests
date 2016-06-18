#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<deque>
#include<cstdio>

using namespace std;

struct Foo
{
	string nome;
	int pos;
};

void shellsort(deque<Foo> &vet)
{
	int i = 0;
	while (true)
	{
		bool isSorted = true;
		deque<Foo>::iterator ite = vet.begin();
		int max = -1;
		int atual = -1;
		bool isInicio = true;
		if (i+1 >= vet.size()) return;
		for (int k = i+1; k < vet.size(); k++)
		{
			if (vet[k].pos > vet[i].pos && vet[k].pos < atual)
			{
				isSorted = false;
				break;
			}
			else
			{
				if (vet[k].pos > vet[i].pos)
					atual = vet[k].pos;
			}
			if (vet[k].pos < vet[i].pos && vet[k].pos > max)
			{
				ite = vet.begin() + k;
				max = vet[k].pos;				
			}
		}
		if (!i && vet[i].pos == 0 && isSorted)
		{
			break;
		}
		isInicio= false;
		if (isSorted && max >= 0)
		{
			vet.push_front(*ite);
			cout << (*ite).nome << endl;
			vet.erase(ite);
			i = 0;
		}
		else
			i++;										
	}
}


int main()
{
	//freopen("int.txt", "r", stdin);
	
	int nTest;
	cin >> nTest;
	for (int t = 0; t < nTest; t++)
	{
		if (t) cout << endl;
		int n;
		cin >> n;
		getchar();
		vector<string> inicio(n);
		map<string, int> final;
		for (int i = 0; i < n; i++)
		{
			string line;
			char str[100];
			gets(str);
			line = str;
			inicio[i] = line;
		}
		
		for (int i = 0; i < n; i++)
		{
			string line;
			char str[100];
			gets(str);
			line = str;
			final[line] = i;			
		}
		deque<Foo> pos(n);
		for (int i = 0; i < inicio.size(); i++)
		{
			pos[i].pos = final[inicio[i]];
			pos[i].nome = inicio[i];
		}
		shellsort(pos);
	}
	return 0;
}

