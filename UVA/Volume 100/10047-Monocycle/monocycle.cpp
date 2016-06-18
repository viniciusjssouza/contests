/**************************************************************
* UVa 10047 - Monocycle - Programming Challenges
* 
* Autor: Vinicius J. S. Souza
* Data: 06/11/2009
* Tecnicas: bfs
**********************************************************/


#include<iostream>
#include<algorithm>
#include<deque>
#include<string>

#define FREE 		0x7FFFFFFF
#define BLOCKED 	-2

#define RED			2
#define BLACK		1
#define GREEN		0
#define WHITE		4
#define BLUE		3

#define NORTH	0
#define EAST	1
#define WEST	2
#define SOUTH   3   	

using namespace std;

typedef pair<int, int> point;

int K, L;
int grid[25][25][5][4];

point source, target;

struct Square
{
	int color;
	int lin;
	int col;
	int time; 
	int dir;

	Square(int color, int lin, int col, int time, int dir):color(color), lin(lin), col(col),
		time(time), dir(dir){}
};

int nextColor(int color)
{
	return (color >= WHITE ? GREEN : color+1);
}

int moveTime(int dir1, int dir2)
{
	if (dir1 == dir2)
		return 1;
	if (dir1 == NORTH)
	{
		if (dir2 == EAST || dir2 == WEST)
			return 2;
		else if (dir2 == SOUTH)
			return 3;
	}	
	else if (dir1 == EAST)
	{
		if (dir2 == NORTH || dir2 == SOUTH)
			return 2;
		else if (dir2 == WEST)
			return 3;
	}
	else if (dir1 == SOUTH)
	{
		if (dir2 == EAST || dir2 == WEST)
			return 2;
		else if (dir2 == NORTH)
			return 3;
	}
	else if (dir1 == WEST)
	{
		if (dir2 == NORTH || dir2 == SOUTH)
			return 2;
		else if (dir2 == EAST)
			return 3;
	}
	return FREE;
}

int bfs()
{
	deque<Square> fila;
	Square current(GREEN, source.first, source.second, 0, NORTH);
	fila.push_back(current);
	grid[current.lin][current.col][GREEN][NORTH] = 0;
	int minimo = FREE;
	
	while(!fila.empty())
	{
		current = (fila.front());		
		fila.pop_front();
		if (current.time >= minimo)
			continue;
		if (current.lin == target.first && current.col == target.second && current.color == GREEN)
		{
			minimo = min(current.time, minimo);
			continue;
		}
		int time;
		int nextC = nextColor(current.color);
		if (current.lin-1 >= 0 && grid[current.lin-1][current.col][0][0] != BLOCKED &&
				(time = current.time + moveTime(current.dir, NORTH)) < 
						grid[current.lin-1][current.col][nextC][NORTH])
		{
			Square s(nextC, current.lin-1, current.col, time, NORTH);
			fila.push_back(s);
			grid[s.lin][s.col][nextC][NORTH] = s.time;			
		}
		if (current.col+1 < K && grid[current.lin][current.col+1][0][0] != BLOCKED &&
				(time = current.time + moveTime(current.dir, EAST)) < 
					grid[current.lin][current.col+1][nextC][EAST])
		{
			Square s(nextC, current.lin, current.col+1, time, EAST);
			fila.push_back(s);
			grid[s.lin][s.col][nextC][EAST] = s.time;
		}
		if (current.lin+1 < L && grid[current.lin+1][current.col][0][0] != BLOCKED &&
				(time = current.time + moveTime(current.dir, SOUTH)) < grid[current.lin+1][current.col][nextC][SOUTH])
		{
			Square s(nextC, current.lin+1, current.col, time, SOUTH);
			fila.push_back(s);
			grid[s.lin][s.col][nextC][SOUTH] = s.time;
		}
		if (current.col-1 >= 0 && grid[current.lin][current.col-1][0][0] != BLOCKED &&
				(time = current.time + moveTime(current.dir, WEST)) < grid[current.lin][current.col-1][nextC][WEST])
		{
			Square s(nextC, current.lin, current.col-1, time, WEST);
			fila.push_back(s);
			grid[s.lin][s.col][nextC][WEST] = s.time;
		}		
	}
	return minimo;
}

int main()
{	
	int test = 0;
	string line;
	while (true)
	{
		scanf("%d %d", &L, &K);
		if (!L && !K) 
			break;
		if (test) putchar('\n');
		test++;
		getchar();
		for (int i = 0; i < L; i++)
		{		
			getline(cin, line);
			for (int k = 0; k < K; k++)
			{	
				char c = line[k];
				if (c != '#')
				{
					for (int j = 0; j < 5; j++)
						for (int m = 0; m < 4; m++)
							grid[i][k][j][m] = FREE;
					if (c == 'S')
						source = point(i, k);
					else if (c == 'T')
						target = point(i, k);					
				}
				else 
					grid[i][k][0][0] = BLOCKED;
					
			}								
		}
/*
		for (int i = 0; i < L; i++)
		{
			for (int k = 0; k < K; k++)
			{
				if (grid[i][k] == FREE)
					printf
				printf("%d ", grid[i][k][0]);
			}
			putchar('\n');
		}
*/
		int result = bfs();
		printf("Case #%d\n", test);
		if (result < FREE)
			printf("minimum time = %d sec\n", result);			
		else
			printf("destination not reachable\n");
			
	}
	return 0;
}
