/*****************************************************************
 * UVa - 10188 - Automated Judge Script - Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 24/07/2008
 *****************************************************************/

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

const string WA = "Wrong Answer";
const string PE = "Presentation Error";
const string AC = "Accepted";

string avalia(const string &std, const string &team);

int main()
{
//	freopen("input.txt", "r", stdin);
	int x = 0;
	while (true)
	{
		if (feof(stdin)) return 0;
		int n, m;
		cin >> n;
		getchar();
		if (!n) return 0;
		if (feof(stdin)) return 0;
		x++;
		string stdInput;
		string teamInput;
		string line;
		for (int i = 0; i < n; i++)
		{
			getline(cin, line);
			line += "\n";
			stdInput += line;
		}
		if (feof(stdin)) return 0;					
		cin >> m;
		getchar();
		if (feof(stdin)) return 0;					
		for (int i = 0; i < m; i++)
		{
			getline(cin, line);
			line += "\n";
			teamInput += line;
		}
		
		cout << "Run #" << x << ": " << avalia(stdInput, teamInput) << endl;
	}	
}

string avalia(const string &std, const string &team)
{
	bool ac = true;
	bool wa = false;
	if (std != team)
		ac = false;
	if (ac) return AC;
	
	string tN="", stdN = "";
		
	for (int s=0, t = 0; s < std.size() || t < team.size(); s++, t++)
	{
		if (s < std.size() && isdigit(std[s]))
			stdN += std[s];
		if (t < team.size() && isdigit(team[t]))
			tN += team[t];
		//cout << tN << " " << stdN << endl;
	}
	if (tN != stdN) 
		wa = true;
	if (wa) return WA;
	return PE;
}
