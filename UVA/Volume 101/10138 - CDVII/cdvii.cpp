#include<iostream>
#include<string>
#include<map>
#include<set>
#include<cstdlib>
#include<iomanip>
#include<deque>
#include<cmath>

#define BEGIN 1
#define END -1

using namespace std;

struct Trip
{
	int time;
	int distance;
	double toll;
	int tipo;
};

struct Compare
{
	bool operator()(const Trip &a, const Trip &b)
	{
		if (a.time <= b.time)
			return true;
		else
			return false;
	}
};

int main()
{
	//freopen("in.txt", "r", stdin);
	double taxas[24];
	int nTest;
	cin >> nTest;
	for  (int k = 0; k < nTest; k++)
	{
		if (k != 0) cout << endl;
		map<string, set<Trip, Compare> > input;
		set<string> placas;
		for (int i = 0; i < 24; i++)
		{
			cin >> taxas[i];
			taxas[i] /= 100;
		}
		string line;
		int nEnds = 0;
		getchar();
		while (!feof(stdin))
		{
			getline(cin, line);
			if (line == "") break;
			string placa = "";
			int i = 0;
			for (; line[i] != ' '; i++)
				placa += line[i];
			placas.insert(placa);

			string time = "";
			for (int m = i+1; m < (i+12); m++)
				if (isdigit(line[m]))
					time = time + line[m];
			
			Trip trip;
			trip.time = atoi(time.c_str());
			i+=7;
			trip.toll = taxas[atoi(line.substr(i, 2).c_str())];
			
			string km = "";
			i = line.size()-1;
			while (!isdigit(line[i]))
				i--;
			while (isdigit(line[i]))
			{
				km = line[i] + km;
				i--;
			}
			trip.distance = atoi(km.c_str());
			
			if (line.find("enter") != string::npos)
				trip.tipo = BEGIN;
			else
				trip.tipo = END;
			input[placa].insert(trip);
		}
		
		
		for (set<string>::iterator ite = placas.begin(); ite != placas.end(); ite++)
		{
			double total = 0.0;
			bool show = false;
			for (set<Trip>::iterator setIte = input[(*ite)].begin(); setIte != input[(*ite)].end();
					setIte++)
			{
				if ((*setIte).tipo == END) continue;
				Trip trip = (*setIte);
				while (setIte != input[(*ite)].end() && (*setIte).tipo == BEGIN)
				{
					trip = (*setIte);
					setIte++;														
				}
				if (setIte == input[(*ite)].end())
					break;
				show = true;
				double toll = 0.0;
				if (trip.tipo == BEGIN)
					toll = trip.toll;
				else
					toll = (*setIte).toll;
				total += ( (double)(abs((((*setIte).distance - trip.distance)))) * toll + 1.0);				
			}
			if (show)
			{
				cout << (*ite) << " $";
				cout << fixed << setprecision(2) << (total + 2.00) << endl;
			}
		}		
	}
	return 0;
}