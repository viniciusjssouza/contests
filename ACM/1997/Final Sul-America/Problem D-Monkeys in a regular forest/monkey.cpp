/**************************************************************************
* Maratona - Final Brasileira 1998 - Problema D - Monkey in a Regular Forest
* UVA - 776
* Autor: Vinicius J. S. Souza
* Data: 13/03/2009
* Tecnicas utilizadas: travessia de grafos
*****************************************************************************/

#include<iostream>
#include<string>
#include<cstdio>
#include<deque>
#include<vector>
#include<sstream>

using namespace std;

int ncol, nlin;
int proxValor;

int getNumCaracteres(int num)
{
	int conta = 1;
	int div = 10;
	while ((num / div) > 0)
	{
		div *= 10;
		conta++;
	}
	return conta;
}

string removeEspacos(const string& str)
{
	string ret="";
	for (int i = 0; i < str.size(); i++)
		if (str[i] != ' ')
			ret.push_back(str[i]);
	return ret;	
}

void bfs(const vector< string > &dados, int v, vector<bool> &processado, vector<vector<int> > &result)
{
	deque<int> fila;
	fila.push_back(v);
	while (fila.size())
	{
		int next = fila.front();
		fila.pop_front();
		int i = next / ncol;	
		int k = next % ncol;
		result[i][k] = proxValor;
		if (proxValor > result[nlin][k])
			result[nlin][k] = proxValor;
		//processado[next] = true;
		
		int pos = i * ncol + k;
		if ( (k+1) < ncol && dados[i][k] == dados[i][k+1] && !processado[pos+1])
		{
			processado[pos+1] = true;
			fila.push_back(pos+1);
		}
		if ( (k+1) < ncol && (i-1) >= 0 && dados[i][k] == dados[i-1][k+1] && !processado[pos-ncol+1])
		{
			fila.push_back(pos-ncol+1);
			processado[pos-ncol+1] = true;
		}
		if ((i-1) >= 0 && dados[i][k] == dados[i-1][k] && !processado[pos-ncol])
		{
			fila.push_back(pos-ncol);
			processado[pos-ncol] = true;			
		}
		if ( (k-1) >= 0 && (i-1) >= 0 && dados[i][k] == dados[i-1][k-1] && !processado[pos-ncol-1])
		{
			fila.push_back(pos-ncol-1);
			processado[pos-ncol-1] = true;
		}
		if ( (k-1) >= 0 && dados[i][k] == dados[i][k-1] && !processado[pos-1])
		{
			fila.push_back(pos-1);
			processado[pos-1] = true;
		}
		if ( (k-1) >= 0 && (i+1) < nlin && dados[i][k] == dados[i+1][k-1] && !processado[pos+ncol-1])
		{
			fila.push_back(pos+ncol-1);
			processado[pos+ncol-1] = true;
		}
		if ( (i+1) < nlin && dados[i][k] == dados[i+1][k] && !processado[pos+ncol])
		{
			fila.push_back(pos+ncol);		
			processado[pos+ncol] = true;
		}
		if ( (k+1) < ncol && (i+1) < nlin && dados[i][k] == dados[i+1][k+1] && !processado[pos+ncol+1])
		{
			fila.push_back(pos+ncol+1);
			processado[pos+ncol+1]= true;
		}
	}		
}

int main()
{
	string input = "";
	vector<string> dados;
	bool end = false;
	while(!feof(stdin))
	{
		while(1)
		{
			getline(cin, input);
			if (input == "%") break;
			else if (input == "")
			{
				end = true;
				break;
			}
			dados.push_back(removeEspacos(input));
		}
		nlin = dados.size();
		ncol = dados[0].size();

		vector<bool> processado(nlin*ncol, false);
		vector< vector<int> > result(nlin+1, vector<int>(ncol,-1));
		proxValor = 1;
		for (int i = 0; i < processado.size(); i++)
		{
			if (!processado[i])
			{
				bfs(dados, i, processado, result);
				proxValor++;
			}			
		}
		
		for (int i = 0; i < nlin; i++)
		{
			for (int k = 0; k < ncol; k++)
			{
				int nSpaces = getNumCaracteres(result[nlin][k]) - getNumCaracteres(result[i][k]) + 1;
				//cout << "Tam:" << tam << endl;
				if (!k) nSpaces--;
				while(nSpaces--)
					putchar(' ');
				printf("%d", result[i][k]);		
			}
			putchar('\n');
		}
		printf("%\n");
		if (end) return 0;
		dados.clear();
	}
	return 0;
}
