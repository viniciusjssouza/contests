/*****************************************************************************
 *  10267 - Graphical Editor - UVa Contest Problems - 
 *  Autor: Vinicius J. S. Souza 
 *  Data: 25/01/2008
 *****************************************************************************/

#include <cstdio>
#include <iostream>

using namespace std;

int col = 0, lin = 0;
char bitmap[252][252];

struct Pos 
{
	int x;
	int y;
};

void printBitmap()
{
	for (int i =0; i < lin; i++)
	{
		for (int k =0; k < col; k++)
		{
			putchar(bitmap[k][i]);
		}
		putchar('\n');
	}
}

void initBitmap()
{
	for (int i = 0; i < lin; i++)
	{
		for (int k = 0; k < col; k++)
			bitmap[k][i] = 'O';
	}
}

void initAux(bool bmp[252][252])
{
	for (int i = 0; i < lin; i++)
	{
		for (int k = 0; k < col; k++)
			bmp[k][i] = false;
	}
}

void colorVertical(int x, int y1, int y2, char color)
{
	for (int i = y1; i <= y2; i++)
	{
		bitmap[x][i] = color;
	}
}

void colorHorizontal(int x1, int x2, int y, char color)
{
	for (int i = x1; i <= x2; i++)
	{
		bitmap[i][y] = color;
	}
}

void colorRetangulo(int x1, int y1, int x2, int y2, char color)
{
	for (int i = x1; i <= x2; i++)
	{
		for (int k = y1; k <= y2; k++)
		{
			bitmap[i][k] = color;
		}
	}
}

void colorRegiao(bool aux[252][252], int x, int y, char color)
{	
	if ((x-1) >= 0 && (y-1) >= 0 && aux[x-1][y-1] == false && bitmap[x-1][y-1] == bitmap[x][y])
	{
		aux[x-1][y-1] = true;
		colorRegiao(aux, x-1, y-1, color);
	}

	if ((y-1) >= 0 && aux[x][y-1] == false && bitmap[x][y-1] == bitmap[x][y])
	{
		aux[x][y-1] = true;
		colorRegiao(aux, x, y-1, color);
	}

	if ((x+1) < col && (y-1) >= 0 && aux[x+1][y-1] == false && bitmap[x+1][y-1] == bitmap[x][y])
	{
		aux[x+1][y-1] = true;
		colorRegiao(aux, x+1, y-1, color);
	}

	if ((x-1) >= 0 && aux[x-1][y] == false && bitmap[x-1][y] == bitmap[x][y])
	{
		aux[x-1][y] = true;
		colorRegiao(aux, x-1, y, color);
	}

	if ((x+1) < col && aux[x+1][y] == false && bitmap[x+1][y] == bitmap[x][y])
	{
		aux[x+1][y] = true;
		colorRegiao(aux, x+1, y, color);
	}

	/////////////// Diagonal inferior esquerda /////////////
	if ((x-1) >= 0 && (y+1) < lin && aux[x-1][y+1] == false && bitmap[x-1][y+1] == bitmap[x][y])
	{
		aux[x-1][y+1] = true;
		colorRegiao(aux, x-1, y+1, color);
	}

	if ((y+1) < lin && aux[x][y+1] == false && bitmap[x][y+1] == bitmap[x][y])
	{
		aux[x][y+1] = true;
		colorRegiao(aux, x, y+1, color);
	}

	if ((x+1) < lin && (y+1) < col && aux[x+1][y+1] == false && bitmap[x+1][y+1] == bitmap[x][y])
	{
		aux[x+1][y+1] = true;
		colorRegiao(aux, x+1, y+1, color);
	}
	bitmap[x][y] = color;
}

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(true)
	{
		char cmd[1000];
		cin >> cmd;
				
		if (cmd[0] == 'X')
			return 0;
		
		else if (cmd[0] == 'I')
		{
			cin >> col >> lin;
			initBitmap();

		}		 	
		else if (cmd[0] == 'C')
		{
			for (int k =0; k < col; k++)
		  	{
				for (int i = 0; i < lin; i++)
				{
					bitmap[k][i] = 'O';
				}
		  	}
		}
	
		else if (cmd[0] == 'L')
		{
			int x = 0, y = 0;
			char color;
			cin >> x >> y >> color;
			x--; y--;
			bitmap[x][y] = color;
		}
	
		else if (cmd[0] == 'V')
		{
			int x=0, y1=0, y2=0;
			char color;
			cin >> x >> y1 >> y2 >> color;
			x--; y1--; y2--;
			if (y1 < y2)
				colorVertical(x, y1, y2, color);
			else
				colorVertical(x, y2, y1, color);
		}
		
		else if (cmd[0] == 'H')
		{
			int x1 = 0, x2 = 0, y = 0;
			char color;
			cin >> x1 >> x2 >> y >> color;
			x1--; x2--; y--;
			if (x1 < x2)
				colorHorizontal(x1, x2, y, color);
			else
				colorHorizontal(x2, x1, y, color);			
		}
		
		else if (cmd[0] == 'K')
		{
			int x1=0, x2=0, y1=0, y2=0;
			char color;
			cin >> x1 >> y1 >> x2 >> y2 >> color;
			x1--; y1--; x2--; y2--;
			colorRetangulo(x1, y1, x2, y2, color);			
		}

		else if (cmd[0] == 'S')
		{
			char fileName[10000];
			cin >> fileName;
			cout << fileName << endl;
			printBitmap();
		}
	
		else if (cmd[0] == 'F')
		{
			bool aux[252][252];
			initAux(aux);
			int x = 0, y = 0;
			char color;
			cin >> x >> y >> color;
			x--; y--;
			colorRegiao(aux, x, y, color);
		}
	 
	}
}
