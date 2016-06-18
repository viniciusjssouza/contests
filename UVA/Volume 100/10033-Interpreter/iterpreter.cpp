/***********************************************************************
 * UVa Problem 10033 - Interpreter - Programming Challenges
 * Autor: Vinicius J. S. Souza
 * Data: 18/01/2008 
 ***********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

void doMod(int &result);

int main()
{
	freopen("input.txt", "r", stdin);
	bool isInicio = true;
	
	int n = 0;
	scanf("%d\n", &n);
	for (int i=0; i < n; i++)
	{
		vector<string> registers;
		vector<string> ram;
		
		if (! isInicio) cout << endl;
		else isInicio = false;
		
		//inicializa os registradores
		for (int k = 0; k < 10; k++)
		{
			registers.push_back("000");
		}
		
		//inicializa a RAM
		while (true)
		{
			char s[5];
			if(gets(s) == NULL) break;
			if (s[0] == NULL)break;
			ram.push_back(s);
		}
		//popula o resto da RAM
		
		while (ram.size() < 1000)
			ram.push_back("000");
		
		//mostra a entrada.
		/*
		for (int k = 0; k < ram.size(); k++)
		{
			cout << ram[k] << endl;
		}
		cout << endl;
		*/
		
		int conta = 0;
		// executa a logica
		for (int k = 0; k < ram.size(); k++)
		{
			string cmd = ram[k];
			conta++;
			//halt
			if (cmd[0] == '1' && cmd[1] == '0' && cmd[2] == '0')
			{
				break;
			}
			else if (cmd[0] == '2')
			{
				int d = cmd[1] - '0';
				int n = cmd[2] - '0';
				char aux[80];
				sprintf(aux, "%d", n);
				registers[d] = aux;
			}
			else if (cmd[0] == '3')
			{
				int d = cmd[1] - '0';
				int n = cmd[2] - '0';
				char aux[80];
				int result = (atoi(registers[d].c_str()) + n);
				doMod(result);
				sprintf(aux, "%d", result);
				registers[d] = aux;
			}
			else if (cmd[0] == '4')
			{
				int d = cmd[1] - '0';
				int n = cmd[2] - '0';
				char aux[80];
				int result = (atoi(registers[d].c_str()) * n);
				doMod(result);
				sprintf(aux, "%d", result);
				registers[d] = aux;
			}
			else if (cmd[0] == '5')
			{
				int d = cmd[1] - '0';
				int s = cmd[2] - '0';
				registers[d] = registers[s];
			}
			else if (cmd[0] == '6')
			{
				int d = cmd[1] - '0';
				int s = cmd[2] - '0';
				char aux[80];
				int result = (atoi(registers[d].c_str()) + atoi(registers[s].c_str()));
				doMod(result);
				sprintf(aux, "%d", result);
				registers[d] = aux;
			}
			else if (cmd[0] == '7')
			{
				int d = cmd[1] - '0';
				int s = cmd[2] - '0';
				char aux[80];
				int result = (atoi(registers[d].c_str()) * atoi(registers[s].c_str()));
				sprintf(aux, "%d", result);
				registers[d] = aux;
			}
			else if (cmd[0] == '8')
			{
				int d = cmd[1] - '0';
				int a = cmd[2] - '0';
				int address = atoi(registers[a].c_str());
				int value = atoi(ram[address].c_str());
				char aux[80];
				sprintf(aux, "%d", value);
				registers[d] = aux;
			}
			else if (cmd[0] == '9')
			{
				int s = cmd[1] - '0';
				int a = cmd[2] - '0';
				int address = atoi(registers[a].c_str());
				ram[address] = registers[s];
			}
			else if (cmd[0] == '0')
			{
				int d = cmd[1] - '0';
				int s = cmd[2] - '0';
				bool has0 = false;
				if (atoi(registers[s].c_str()) != 0)
				{
					k = atoi(registers[d].c_str());
					k--;
				}
			}
			else
			{
				conta--;
			}
		}
		cout << conta << endl;		
	}
}

void doMod(int &result)
{
	if (result >= 1000)
		result = result % 1000;
}
