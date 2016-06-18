/*************************************************************************************************
* UVA 10158 - War - Programming Challenges 
*
* Autor: Vinicius J. S. Souza
* Data:  26/05/2009
* Tecnicas utilizadas: teoria de conjuntos, grafos e estruturas de dados
***************************************************************************************************/

#include<iostream>
#include<vector>

#define SET_FRIEND 1
#define SET_ENEMY 2
#define ARE_FRIENDS 3
#define ARE_ENEMIES 4

using namespace std;

int main()
{
	int n, c, x, y;
	int set = 1;
	scanf("%d", &n);
	vector<int> people(n, 0);
	while (true)
	{
		scanf("%d %d %d", &c, &x, &y);
		if (!c && !x && !y) break;
		
		if (c == SET_FRIEND)
		{
			if (people[x] == -people[y] && people[x]) 
			{
				printf("-1\n");
				continue;
			}
			if (!people[x] && !people[y])
			{
				people[x] = people[y] = set;
				set++;
			}
			else if (people[x] && !people[y])
				people[y] = people[x];
			else if (!people[x] && people[y])
				people[x] = people[y];
			else
			{
				int temp = people[y];
				people[y] = people[x];
				for (int i= 0; i < people.size(); i++)
				{
					if (people[i] == people[x] || people[i] == temp)
						people[i] = people[x];
					else if (people[i] == -people[x] || people[i] == -temp)
						people[i] = -people[x];				
				}
			} 
		}
		else if (c == SET_ENEMY)
		{
			if ( (people[x] == people[y] && people[x]) || (x == y)) 
			{
				printf("-1\n");
				continue;
			}

			if (!people[x] && !people[y])
			{
				people[x] = set;
				people[y] = -set;
				set++;
			}
			else if (people[x] && !people[y])
				people[y] = -people[x];
			else if (!people[x] && people[y])
				people[x] = -people[y];
			else
			{
				int temp = people[y];
				people[y] = -people[x];
				for (int i= 0; i < people.size(); i++)
				{
					if (people[i] == temp)
						people[i] = people[y];	
					else if (people[i] == -temp)
						people[i] = people[x];
				}
			}
		}
		else if (c == ARE_FRIENDS)
		{
			if (people[x] == people[y] && people[x]) printf("1\n");
			else printf("0\n");
		}
		else
		{
			if (people[x] == -people[y] && people[x]) printf("1\n");
			else printf("0\n");
		}	

		/*
		for (int i = 0; i < people.size(); i++)
			cout << i << ": " << people[i] << " -- \n" ;
		cout << "\n-----------------\n";
		*/
	}
	return 0;
}
