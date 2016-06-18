// 10191 - Longest Nap
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<iomanip>

using namespace std;

struct Compromisso
{
	int inicioH;
	int inicioM;
	int fimH;
	int fimM;
};

bool compara(Compromisso a, Compromisso b)
{
	if (a.inicioH < b.inicioH)
		return true;
	else if (a.inicioH > b.inicioH)
		return false;
	else
	{
		if (a.inicioM < b.inicioM)
			return true;
		else
			return false;
	}
}

int getNap(Compromisso *a, Compromisso *b)
{
	if (a == NULL)
	{
		int total = (b->inicioH - 10) * 60;
		total += b->inicioM;
		return total;		
	}
	else if (b == NULL)
	{
		int total = 1080 - (a->fimH * 60 + a->fimM);
		return total;
	}
	else
	{
		int total = (b->inicioH * 60 + b->inicioM) - (a->fimH * 60 + a->fimM);
		return total;
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int n; int day = 1;
	while (! feof(stdin))
	{
		if (!cin.good()) break;
		cin >> n;
		if (!cin.good()) break;
		getchar();
		string line;
		vector<Compromisso> agenda(n);
		for (int i = 0; i < n; i++)
		{
			Compromisso c;
			getline(cin, line);
			c.inicioH = atoi((line.substr(0,2)).c_str());
			c.inicioM = atoi((line.substr(3,2)).c_str());
						
			c.fimH = atoi((line.substr(6,2)).c_str());
			c.fimM = atoi((line.substr(9,2)).c_str());

			agenda[i] = c;			
		}
			
		int max = -1;
		Compromisso c;
		
		if (agenda.size() == 0)
		{
			max = 480;
			c.fimH = 10;
			c.fimM = 0;
		}		
		else if (agenda.size() == 1)
		{
			int nap1 = getNap(NULL, &agenda[0]);
			int nap2 = getNap(&agenda[0], NULL);
			if (nap2 > nap1)
			{
				max = nap2;
				c.fimH = agenda[0].fimH;
				c.fimM = agenda[0].fimM;
			}
			else
			{
				max = nap1;
				c.fimH = 10;
				c.fimM = 0;
			}
		}
		
		else
		{
			sort(agenda.begin(), agenda.end(), compara);
			max = getNap(NULL, &agenda[0]);
			c.fimH = 10;
			c.fimM = 0;
			for (int i = 0; i < agenda.size(); i++)
			{
				int x;
				if (i == (agenda.size() - 1))
				{
					x = getNap(&agenda[i], NULL);				
				}
				else
				{
					x = getNap(&agenda[i], &agenda[i+1]);
				}
				if (x > max)
				{
					max = x;
					//cout << i << endl;
					if (i < 0)
					{
						c.fimH = 10;
						c.fimM = 0;
					}
					else 
						c = agenda[i];
				}
			}
		}
		int hours = max / 60;
		int minutes = max % 60;
		cout.fill('0');
		cout << "Day #" << day << ": the longest nap starts at ";
		cout << setw(2) << c.fimH;
		cout << ':';
		cout << setw(2) << c.fimM;
		cout << " and will last for ";
		if (hours > 0)
			cout << hours << " hours and ";
		cout << minutes << " minutes.\n"; 
		day++;
	}
	//system("pause");
	return 0;
}
