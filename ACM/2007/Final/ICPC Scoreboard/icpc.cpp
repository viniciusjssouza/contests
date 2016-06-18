#include<iostream>
#include<string>
#include<cstdlib>
#include<set>

using namespace std;

struct Time
{
	int id;
	int solved;
	int tries;
	int time;
	int total;
};

struct cmp
{
	bool operator()(Time a, Time b)
	{
		if (a.solved > b.solved) return true;
		else if (a.solved < b.solved) return false;
	
		if (a.total < b.total) return true;
		else if (b.total < a.total)return false;
		
		if (a.id < b.id) return true;
		return false;
	}	
};

multiset<Time, cmp> score;
int nTeams = 0, nProblems = 0;

void getInput()
{
	for (int i = 0; i < nTeams; i++)
	{
		string line = "";
		Time time;
		time.id = i; time.solved = 0; time.time = 0; time.tries = 0;
		getline(cin, line);
		int m = 0;					
		for (int k = 0; k < nProblems; k++)
		{
			string num="";
			for (; isdigit(line[m]); m++)
				num += line[m];
			m++;
			int tries = atoi(num.c_str());
			if (tries) tries--;
			num = "";
			for (; isdigit(line[m]); m++)
				num += line[m];
			while (!isdigit(line[m]))
				m ++;
			if (num != "")
			{
				time.tries += tries;
				time.solved++;
				time.time += atoi(num.c_str());
			}
		}
		time.total = time.time + 20*time.tries;
		score.insert(time);
	}
}

bool changed(int ep)
{
	multiset<Time, cmp> aux;
	for (multiset<Time>::iterator ite = score.begin(); ite != score.end(); ite++)
	{
		Time time; time.id = (*ite).id; time.solved = (*ite).solved; 
		time.time = (*ite).time; time.tries = (*ite).tries; 
		time.total = (*ite).time + ep * (*ite).tries;
		aux.insert(time);
	}
	
	for (multiset<Time>::iterator ite = score.begin(), auxIte = aux.begin(); ite != score.end() && auxIte != aux.end(); ite++, auxIte++)
	{
		if ((*auxIte).id != (*ite).id)
			return true;
		if (ite == score.begin()) continue;
		multiset<Time>::iterator empIte = ite; empIte--;
		multiset<Time>::iterator empAux = auxIte; empAux--;		
		if ((*ite).solved == (*empIte).solved && (*ite).total == (*empIte).total && 
			((*auxIte).solved != (*empAux).solved || (*auxIte).total != (*empAux).total))
				return true;
		if ((*ite).total != (*empIte).total &&  
			((*auxIte).solved == (*empAux).solved && (*auxIte).total == (*empAux).total))
				return true;
				
	}	
	return false;
}

int main()
{
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	while (1)
	{
		cin >> nTeams >> nProblems;
		score.clear();
		getchar();
		if (!nTeams && !nProblems) break;
		getInput();	
		int min = 1, max = 1;
		multiset<Time>::iterator ite = score.end(); ite--;
		multiset<Time>::iterator acima = ite; acima--;
		for(; ite != score.begin(); ite--, acima--)
		{			
			if ((*ite).solved == (*acima).solved && 
				((*ite).time != (*acima).time || (*ite).tries != (*acima).tries) &&
				((*ite).tries || (*acima).tries))
			{
				min = -1;
				break;
			}
		}
		
		if (min < 0)
		{
			//aplica o metodo dividir para conquistar
			int inicio = 20, fim = 1, aux = 10;
			while ((inicio - fim) > 2 && aux > 1)
			{
				if (!changed(aux))
					inicio = aux;
				else
					fim = aux;
				aux = (inicio + fim) / 2;
			}
			if (!changed(fim))min = fim;
			else if (!changed(aux)) min = aux;
			else min = inicio;			
		}		
		
		ite = score.end(); ite--;
		acima = ite; acima--;
		for(; ite != score.begin(); ite--, acima--)
		{			
			if ((*ite).solved == (*acima).solved && 
				((*ite).time != (*acima).time || (*ite).tries != (*acima).tries) &&  
				(*acima).tries)
			{
				max = -1;
				break;
			}
		}
		
		if (max < 0)
		{
			//realiza o metodo de dividir para conquistar
			bool flag = false;
			int inicio = 20, fim = 40, aux = 30;
			while ((fim - inicio) > 2)
			{
				if (!changed(aux))
				{
					inicio = aux;
					if (!flag) fim = 2 * aux;
				}
				else
				{
					fim = aux;
					flag = true;
				}
				aux = (inicio + fim) / 2;
			}
			if (!changed(fim))max = fim;
			else if (!changed(aux)) max = aux;
			else max = inicio;			
		}			
		
		cout << min << ' ';
		// 3000000 eh o valor maximo que se pode atingir
		if (max <= 1 || max > 300000) cout << '*';
		else cout << max;
		cout << endl;
	}
	return 0;
}