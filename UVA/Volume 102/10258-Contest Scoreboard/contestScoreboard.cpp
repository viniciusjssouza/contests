/***************************************************************
 * Problema 10258 - Contest Scoreboard - Livro Programming Chellenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 08/07/2008
 ***************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

class Contestant
{
public:
	bool solved[10];
	bool isInContest;
	int penalty;
	int acc_penalty[10];
	int number;
	int nSolved;
	
	Contestant()
	{
		for (int i =0; i < 10; i++)
		{
			solved[i] = false;
			acc_penalty[i] = 0;
		}
		nSolved = 0;
		penalty = 0;
		isInContest = false;
	}
	
	bool solve(int p)
	{
		if (!this->solved[p]) 
		{
			this->solved[p] = true;
			this->nSolved++;
			return true;
		}
		return false;
	}
};

struct compare_contestant : public binary_function<Contestant, Contestant, bool> 
{
	bool operator()(Contestant x, Contestant y) 
	{ 
		if (x.nSolved > y.nSolved)
			return true;
		else if (x.nSolved < y.nSolved) return false;
		else
		{
			if (x.penalty < y.penalty)
				return true;
			else if (x.penalty > y.penalty)
				return false;
			else
			{
				if (x.number < y.number) return true;
				else return false;
			}
		}
		return true;
	}
};

int main()
{
	//freopen("input.txt", "r", stdin);
	bool isInicio = true;
	int numCases = 0;
	cin >> numCases;
	getchar();
	getchar();
	for (int i = 0; i < numCases; i++)
	{
		vector<Contestant> contest(100);
		if (!isInicio)
			cout << endl;			
		else isInicio = false;
		for (int k = 0; k < contest.size(); k++)
			contest[k].number = k+1;

		while (1)
		{
			string line;
			getline(cin, line);
			istringstream iss(line);
			int c;
			if (line == "") break;
			while (iss >> c)
			{
				c--;
				contest[c].isInContest = true;
				int problem; int penalty; char l;
				iss >> problem;
				problem--;
				iss >> penalty;
				iss >> l;
				//cout << c+1 << " " << problem << " " << penalty << " " << l << endl;
				if (l == 'C')
				{
					//cout << c << "\n";
					if (contest[c].solve(problem))
						contest[c].penalty += penalty + contest[c].acc_penalty[problem];
				}
				else if (l == 'I')
				{
					contest[c].acc_penalty[problem] += 20;
				}
			}
		}
		sort(contest.begin(), contest.end(), compare_contestant());
		
		for (int k = 0; k < contest.size(); k++)
		{
			if (contest[k].isInContest)
			{
				Contestant c = contest[k];
				cout << c.number  << " " << c.nSolved << " " << c.penalty << endl;
			}
		}
	}
	return 0;
}
