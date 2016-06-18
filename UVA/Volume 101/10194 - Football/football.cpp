#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<cstdlib>

using namespace std;

class Time
{
public:
	string nome;
	int pontos;
	int nJogos;
	int vitorias;
	int empates;
	int derrotas;
	int golsM;
	int golsS;
	
	Time()
	{
		pontos = nJogos = vitorias = empates = derrotas = 
			golsM = golsS = 0;
	}
};

struct Compare
{
	bool operator()(const Time &a,const  Time &b)
	{
		if (a.pontos > b.pontos)
			return true;
		else if (b.pontos > a.pontos)
			return false;
		
		if (a.vitorias > b.vitorias)
			return true;
		else if (b.vitorias > a.vitorias)
			return false;
		
		if ((a.golsM - a.golsS) > (b.golsM - b.golsS))
				return true;
		else if ((a.golsM - a.golsS) < (b.golsM - b.golsS))
				return false;	
		
		if (a.golsM > b.golsM)
				return true;
		else if (b.golsM > a.golsM)
				return false;
		
		if (a.nJogos < b.nJogos)
				return true;
		else if (b.nJogos < a.nJogos)
				return false;
		string str1 = "", str2 = "";
		for (int i = 0; i < a.nome.size(); i++)
			str1 += tolower(a.nome[i]);
		for (int i = 0; i < b.nome.size(); i++)
			str2 += tolower(b.nome[i]);
		if (str1 < str2)
				return true;
		else
				return false;
	}
};

int main()
{
	//freopen("in.txt", "r", stdin);

	int nTest = 0;
	cin >> nTest;
	getchar();
	for (int t = 0; t < nTest; t++)
	{
		if (t) cout << endl;
		string nomeTorneio;
		getline(cin, nomeTorneio);
		
		int nTimes;
		cin >> nTimes;
		getchar();
		map<string, Time> input;
		vector<string> nomes(nTimes);
		for (int i = 0; i < nTimes; i++)
		{
			getline(cin, nomes[i]);
			input[nomes[i]].nome = nomes[i];			
		}
		
		int nJogos;
		cin >> nJogos;
		getchar();
		for (int i = 0; i < nJogos; i++)
		{
			string line;
			getline(cin, line);
			string time1, time2;
			int gols1, gols2;
			
			int aux1 = line.find_first_of("#");
			int aux2 = line.find_last_of("#")+1;
			time1 = line.substr(0, aux1);
			time2 = line.substr(aux2, line.size() - aux2);
			
			int conta = aux1 + 1;
			string str = "";
			for (; isdigit(line[conta]); conta++)
				str = str + line[conta]; 
			gols1 = atoi(str.c_str());
			
			str = "";
			for (conta++; isdigit(line[conta]); conta++)
				str = str + line[conta];
			gols2 = atoi(str.c_str());
			
			input[time1].golsM += gols1; input[time2].golsM += gols2;
			input[time1].golsS += gols2; input[time2].golsS += gols1;
			input[time1].nJogos++; 		 input[time2].nJogos ++;
			if (gols1 > gols2)
			{
				input[time1].pontos += 3; 
				input[time1].vitorias++; input[time2].derrotas ++;				
			}							
			else if (gols2 > gols1)
			{
				input[time2].pontos += 3; 
				input[time2].vitorias++; input[time1].derrotas ++;			
			}
			else
			{
				input[time2].pontos ++; input[time1].pontos++;   
				input[time2].empates++; input[time1].empates ++;
			}
		}
		
		set<Time, Compare> tabela;
		for (int i = 0; i < nomes.size(); i++)
			tabela.insert(input[nomes[i]]);
		cout << nomeTorneio << endl;
		int i = 1;
		for (set<Time>::iterator ite = tabela.begin(); ite != tabela.end(); i++, ite++)
		{
			cout << i << ") " << (*ite).nome << ' ';
			cout << (*ite).pontos << "p, " << (*ite).nJogos << "g (";
			cout << (*ite).vitorias << "-" << (*ite).empates << "-" << (*ite).derrotas << "), ";
			cout << ((*ite).golsM - (*ite).golsS) << "gd ("<< (*ite).golsM << "-" << (*ite).golsS << ")\n";
		}
		
	}
	return 0;
}