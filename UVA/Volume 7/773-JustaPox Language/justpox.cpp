/***************************************************************************************
* ACM - 1998 - Final Brasileira - Problem A - JustaPox Language
* UVA - 773
* Autor: Vinicius J. S. Souza
* Data: 28/03/2009
****************************************************************************************/

#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#define  definicao   "is"
#define  atribuicao  "="
#define  qlqValor    " "

using namespace std;

int main()
{
	string linha;
	map<string, int> tamanho;
	map<string, vector<string> > interior;
	while (getline(cin,linha))
	{
		if (!linha.size()) break;
		linha.erase(linha.size()-1, 1);
		stringstream buffer(linha);
		string varNome, operacao;
		buffer >> varNome;
		buffer >> operacao;
		if (operacao == definicao)
		{
			string valor;
			while (buffer >> valor)
			{
				if (valor[0] == '[')
				{
					string aux("");
					int i = 1;
					for (; isdigit(valor[i]); i++)
						aux.push_back(valor[i]);
					int tam = atoi(aux.c_str());
					
					tamanho[varNome] += tam;
					for (int i = 0; i < tam; i++)
						interior[varNome].push_back(qlqValor);
				}			
				else
				{
					tamanho[varNome] += tamanho[valor];
					for (int i = 0; i < tamanho[valor]; i++)
						interior[varNome].push_back(valor);
				}													 
			}				
		}
		else if (operacao == atribuicao)
		{
			vector<int> nums;
			int num = 0;
			while (buffer >> num)
			{
				nums.push_back(num);
				if (nums.size() > tamanho[varNome])
					break;
			}
			if (nums.size() != tamanho[varNome]) 
				cout << linha << '.' << endl;
			else
			{
				map<string, vector<int> > valores;
				map<string, bool> init;
				for (int i = 0; i < nums.size(); )
				{
					if (interior[varNome][i] != qlqValor)
					{
						string aux = interior[varNome][i];
						int pos = i + tamanho[aux];
						if(!init[aux])
						{
							init[aux] = true;
							for (; i < pos && i < nums.size(); i++) 
							{
								valores[aux].push_back(nums[i]);							
		//						cout << nums[i] << " " << aux << endl;
							}
						}
						else
						{
							vector<int> v2;
							for (; i < pos && i < nums.size(); i++) 
							{
								v2.push_back(nums[i]);
		//						cout << nums[i] << " v2 " << aux << endl;
							}
							if (!equal(valores[aux].begin(), 
									valores[aux].end(),
									v2.begin()))
							{
								cout << linha << '.' << endl;							
								break;
							}
						}
					}
					else i++;	
				}
			}
		}
	}
	return 0;
}
