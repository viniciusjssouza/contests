#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<cmath>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<deque>
#include<ctime>

#define TAM 4
#define MAXN 10000

using namespace std;

class Config
{
public:
	int passos;
	int num;

	Config(int num, int passos)
	{
		this->passos = passos;
		this->num = num;
	}	
};

int bfs(const int &init, const int &alvo, const vector<bool> &proibido)
{
	deque<Config> fila;
	vector<bool> processado(MAXN, false);
	
	Config conf(init, 0);
	fila.push_back(conf);

	while (fila.size() && fila[0].num != alvo)
	{
		conf.num = fila[0].num;
		conf.passos = fila[0].passos;
		fila.pop_front();
		if (!processado[conf.num])
		{
			processado[conf.num] = true;
			//cout << "Processando: " << fila[0].id << endl;
			for (int i = 0; i < TAM; i++)
			{
				Config c1(conf.num, conf.passos+1), c2(conf.num, conf.passos+1);
				register int soma = pow((float)10, (float)i);
				register int base = soma * 10;
				register int sub = 9 * soma;
				if (c1.num % base >= sub)
					c1.num -= sub;
				else
					c1.num += soma;

				//cout << "Direita: " << c1.num << endl;
				if (!proibido[c1.num])
					fila.push_back(c1);
				
				if (c2.num % base < soma)
					c2.num += sub;
				else
					c2.num -= soma;
				//cout << "Esquerda: " << c2.num << endl;
				if (!proibido[c2.num])
					fila.push_back(c2);
				
			}	
		}		
	}
	if (!fila.size())
		return -1;
	else 
		return fila[0].passos;
	
}

int main()
{
	int n;
	cin >> n;
	long start = clock();
	while (n--)
	{
		vector<bool> proibido(MAXN, false);
		int init;
		int alvo;
		int n1, n2, n3, n4;
		cin >> n1 >> n2 >> n3 >> n4;
		init = 1000*n1 + 100 * n2 + 10 * n3 + n4;
		cin >> n1 >> n2 >> n3 >> n4;
		alvo = 1000*n1 + 100 * n2 + 10 * n3 + n4;

		int p;
		cin >> p;		
		while (p--)
		{
			cin >> n1 >> n2 >> n3 >> n4;		
			int foo = 1000*n1 + 100 * n2 + 10 * n3 + n4;
			proibido[foo] = true;
		}
		cout << bfs(init, alvo, proibido) << endl;		  
	}
	cout << "Tempo: " << (clock()-start) << endl;
	return 0;
}

