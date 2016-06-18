#include<iostream>
#include<cstdio>
#include<string>
#include<vector>

#define boundsUp  (i-1 >= 0)
#define boundsDown  (i+1 < r)
#define boundsLeft  (k-1 >= 0)
#define boundsRight  (k+1 < c)

#define CLOCK	1
#define COUNTER	-1

using namespace std;

vector<string> in;
int r, c;

int main()
{
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
		
	while (1)
	{
		cin >> r >> c;
		if (!r && !c) break;
		in = vector<string>(r);
		for (int i = 0; i < r; i++)
			cin >> in[i];
		cout << "\n";
		vector<vector<int>  > init(r);
		vector<vector<bool> >blocked(r);
		for (int i = 0; i < r; i++)
		{
			init[i] = vector<int>(c,0);
			blocked[i] = vector<bool>(c,0);
		}
		
		for (int i = 0; i < r; i++)
		{
			for (int k = 0; k < c; k++)
			{				
				if (in[i][k] == 'I')
				{					
					if (boundsRight && in[i][k+1] == 'I')
					{
						blocked[i][k] = true;
						blocked[i][k+1] = true;
					}
					if (boundsRight && boundsUp && in[i-1][k+1] == 'I')
					{
						blocked[i][k] = true;
						blocked[i-1][k+1] = true;
					}
					if (boundsUp && in[i-1][k] == 'I')
					{
						blocked[i][k] = true;
						blocked[i-1][k] = true;
					}
					if (boundsLeft && in[i][k-1] == 'I')
					{
						blocked[i][k] = true;
						blocked[i][k-1] = true;
					}
					if (boundsLeft && boundsDown && in[i+1][k-1] == 'I')
					{
						blocked[i][k] = true;
						blocked[i+1][k-1] = true;
					}
					if (boundsDown && in[i+1][k] == 'I')
					{
						blocked[i][k] = true;
						blocked[i+1][k] = true;
					}
					if (!blocked[i][k])
						init[i][k]= CLOCK;
					if (boundsRight && in[i][k+1] != '.' && !blocked[i][k+1])
						 	init[i][k+1] = COUNTER;
					if (boundsRight && boundsUp && in[i-1][k+1] != '.' && !blocked[i-1][k+1]) 
						init[i-1][k+1] = COUNTER;
					if (boundsUp && in[i-1][k] != '.' && !blocked[i-1][k])
							init[i-1][k] = COUNTER;
					if (boundsLeft && in[i][k-1] != '.' && !blocked[i][k-1])
							init[i][k-1] = COUNTER;
					if (boundsLeft && boundsDown && in[i+1][k-1] != '.' && !blocked[i+1][k-1])
							init[i+1][k-1] = COUNTER;
					if (boundsDown && in[i+1][k] != '.' && !blocked[i+1][k])
							init[i+1][k] = COUNTER;
				}
			}
		}

		for (int i = 0; i < r; i++)
		{
			for (int k = 0; k < c; k++)
			{
				if (in[i][k] != '.' && !blocked[i][k] && init[i][k])
				{
					if (boundsRight && in[i][k+1] != '.' && !blocked[i][k+1])
					{
						if (init[i][k] == init[i][k+1] && init[i][k])
							blocked[i][k+1] = true;
						else init[i][k+1] = -init[i][k];
					}
					if (boundsRight && boundsUp && in[i-1][k+1] != '.' && !blocked[i-1][k+1])
					{
						if (init[i][k] == init[i-1][k+1] && init[i][k])
							blocked[i-1][k+1] = true;
						else init[i-1][k+1] = -init[i][k];
					}
					if (boundsUp && in[i-1][k] != '.' && !blocked[i-1][k])
					{
						if (init[i][k] == init[i-1][k] && init[i][k] )
							blocked[i-1][k] = true;
						else init[i-1][k] = -init[i][k];
					}
					if (boundsLeft && in[i][k-1] != '.' && !blocked[i][k-1])
					{
						if (init[i][k] == init[i][k-1] && init[i][k])
							blocked[i][k-1] = true;
						else init[i][k-1] = -init[i][k];
					}
					if (boundsLeft && boundsDown && in[i+1][k-1] != '.' && !blocked[i+1][k-1])
					{
						if (init[i][k] == init[i+1][k-1] && init[i][k])
							blocked[i+1][k-1] = true;
						else init[i+1][k-1] = -init[i][k];
					}
					if (boundsDown && in[i+1][k] != '.' && !blocked[i+1][k])
					{
						if (init[i][k] == init[i+1][k] && init[i][k])
							blocked[i+1][k] = true;
						else init[i+1][k] = -init[i][k];
					}
				}
			}
		}

		for (int i = r-1; i >= 0; i--)
		{
			for (int k = c-1; k >= 0; k--)
			{
				if (in[i][k] != '.' && !blocked[i][k] && init[i][k])
				{
					if (boundsRight && in[i][k+1] != '.' && !blocked[i][k+1])
					{
						if (init[i][k] == init[i][k+1] && init[i][k])
							blocked[i][k+1] = true;
						else if (!init[i][k+1]) 
						{
							init[i][k+1] = -init[i][k];
							k+=2; continue;
						}
					}
					if (boundsRight && boundsUp && in[i-1][k+1] != '.' && !blocked[i-1][k+1])
					{
						if (init[i][k] == init[i-1][k+1] && init[i][k])
							blocked[i-1][k+1] = true;
						else if (!init[i-1][k+1]) init[i-1][k+1] = -init[i][k];
					}
					if (boundsUp && in[i-1][k] != '.' && !blocked[i-1][k])
					{
						if (init[i][k] == init[i-1][k] && init[i][k])
							blocked[i-1][k] = true;
						else if (!init[i-1][k]) init[i-1][k] = -init[i][k];
					}
					if (boundsLeft && in[i][k-1] != '.' && !blocked[i][k-1])
					{
						if (init[i][k] == init[i][k-1] && init[i][k])
							blocked[i][k-1] = true;
						else if (!init[i][k-1])init[i][k-1] = -init[i][k];
					}
					if (boundsLeft && boundsDown && in[i+1][k-1] != '.' && !blocked[i+1][k-1])
					{
						if (init[i][k] == init[i+1][k-1] && init[i][k])
							blocked[i+1][k-1] = true;
						else if (!init[i+1][k-1])
						{
							init[i+1][k-1] = -init[i][k];
							i++; continue;
						}
					}
					if (boundsDown && in[i+1][k] != '.' && !blocked[i+1][k])
					{
						if (init[i][k] == init[i+1][k] && init[i][k])
							blocked[i+1][k] = true;
						else if (!init[i+1][k])
						{
							init[i+1][k] = -init[i][k];
							i++; continue;
						}
					}
				}
			}
		}
		

		
		for (int i = 0; i < r; i++)
		{
			for (int k= 0; k < c; k++)
			{
				if (blocked[i][k])
				{
					if (boundsRight && in[i][k+1] != '.')
						blocked[i][k+1] = true;
					if (boundsRight && boundsUp && in[i-1][k+1] != '.' && !blocked[i-1][k+1])
					{
						blocked[i-1][k+1] = true;
						i--;k--;continue;
					}
					if (boundsUp && in[i-1][k] != '.' && !blocked[i-1][k])
					{
						blocked[i-1][k] = true;
						i--;k--; continue;
					}
					if (boundsLeft && in[i][k-1] != '.' && !blocked[i][k-1])
					{
						blocked[i][k-1] = true;
						k-=2; continue;
					}
					if (boundsLeft && boundsDown && in[i+1][k-1] != '.')
						blocked[i+1][k-1] = true;
					if (boundsDown && in[i+1][k] != '.')
						blocked[i+1][k] = true;
				}
			}
		}
		for (int i = 0; i < r; i++)
		{
			for (int k = 0; k < c; k++)
			{
				if (init[i][k] > 0 && !blocked[i][k])
					putchar('(');
				else if (init[i][k] < 0 && !blocked[i][k])
					putchar(')');
				else 
				{
					if (in[i][k] == '.')
						putchar('.');
					else if (blocked[i][k])
						putchar('B');
					else
						putchar('F');
				}
			}
			putchar('\n');
		}
	}
	
	return 0;	
}
	