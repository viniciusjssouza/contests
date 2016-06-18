/***********************************************************************
 * UVa Problem 10196 - Check the Check - Programming Challenges
 * Autor: Vinicius J. S. Souza
 * Data: 11/02/2008 
 ***********************************************************************/
#include <iostream>
#include <cstdio>

// B de "black" e W de "white"
#define   	REI_B_IN_CHECK		1
#define 	REI_W_IN_CHECK		2
#define 	NO_CHECK			0

#define		REI_B				'k'
#define		RAINHA_B			'q'
#define		BISPO_B				'b'
#define 	TORRE_B				'r'
#define 	CAVALO_B			'n'
#define 	PIAO_B				'p'

#define		REI_W				'K'
#define		RAINHA_W			'Q'
#define		BISPO_W				'B'
#define 	TORRE_W				'R'
#define 	CAVALO_W			'N'
#define 	PIAO_W				'P'

using namespace std;

bool isFldEmpty(char fld[10][10]);
int isCheck(char fld[10][10], int i, int k);
bool isValidPos(int pos);

int main()
{
	freopen("input.txt", "r", stdin);
	int conta = 1;
	while (true)
	{
		char fld[10][10];
		
		// recebe todo o campo
		for (int i = 0; i < 8; i++)
			cin >> fld[i];
		
		// Imprime a entrada
		/*
		for (int i = 0; i < 8; i++)
			cout << fld[i] << endl;
		*/
		//verifica se o campo esta todo vazio, terminando o programa em caso positivo.
		if (isFldEmpty(fld)) return 0;
		
		//logica de negocio
		//varredura do campo em busca de situacoes de check
		bool hasCheck = false;
		for (int i = 0; i < 8 && !hasCheck; i++)
		{
			for (int k = 0; k < 8 && !hasCheck; k++)
			{
				if (fld[i][k] != '.')
				{
					int result = isCheck(fld, i, k);
					if (result == REI_B_IN_CHECK)
					{
						printf("Game #%d: black king is in check.\n", conta);
						hasCheck = true;
						break;
					}
					else if (result == REI_W_IN_CHECK)
					{
						printf("Game #%d: white king is in check.\n", conta);
						hasCheck = true;
						break;
					}
				}
			}
		}
		if (! hasCheck)
			printf("Game #%d: no king is in check.\n", conta);
		conta++;
	}
}
	
bool isFldEmpty(char fld[10][10])
{
	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 8; k++)
		{
			if (fld[i][k] != '.')
				return false;
		}
	}
	return true;
}

int isCheck(char fld[10][10], int i, int k)
{
	// avalia pecas Negras
	if (fld[i][k] == REI_B)
	{
		if (isValidPos(i-1) && isValidPos(k-1) && fld[i-1][k-1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i-1) && fld[i-1][k] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k+1) && fld[i-1][k+1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(k-1) && fld[i][k-1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(k+1) && fld[i][k+1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k-1) && fld[i+1][k-1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+1) && fld[i+1][k] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k+1) && fld[i+1][k+1] == REI_W)
			return REI_W_IN_CHECK;
	}
	else if (fld[i][k] == RAINHA_B)
	{
		int lin, col;
		for (lin = i-1, col = k-1; isValidPos(lin) && isValidPos(col); lin--, col--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i-1, col = k+1; isValidPos(lin) && isValidPos(col); lin--, col++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k-1; isValidPos(lin) && isValidPos(col); lin++, col--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k+1; isValidPos(lin) && isValidPos(col); lin++, col++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i-1, col = k; isValidPos(lin) && isValidPos(col); lin--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k; isValidPos(lin) && isValidPos(col); lin++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k-1; isValidPos(lin) && isValidPos(col); col--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k+1; isValidPos(lin) && isValidPos(col); col++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
	}
	else if (fld[i][k] == BISPO_B)
	{
		int lin, col;
		for (lin = i-1, col = k-1; isValidPos(lin) && isValidPos(col); lin--, col--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i-1, col = k+1; isValidPos(lin) && isValidPos(col); lin--, col++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k-1; isValidPos(lin) && isValidPos(col); lin++, col--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k+1; isValidPos(lin) && isValidPos(col); lin++, col++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
	}		
	else if (fld[i][k] == TORRE_B)
	{
		int lin, col;
		for (lin = i-1, col = k; isValidPos(lin) && isValidPos(col); lin--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k; isValidPos(lin) && isValidPos(col); lin++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k-1; isValidPos(lin) && isValidPos(col); col--)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k+1; isValidPos(lin) && isValidPos(col); col++)
		{
			if (fld[lin][col] == REI_W)
				return REI_W_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
	}		
	else if (fld[i][k] == CAVALO_B)
	{
		if (isValidPos(i-2) && isValidPos(k-1) && fld[i-2][k-1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i-2) && isValidPos(k+1) && fld[i-2][k+1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k-2) && fld[i-1][k-2] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k+2) && fld[i-1][k+2] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k-2) && fld[i+1][k-2] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k+2) && fld[i+1][k+2] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+2) && isValidPos(k-1) && fld[i+2][k-1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+2) && isValidPos(k+1) && fld[i+2][k+1] == REI_W)
			return REI_W_IN_CHECK;
	}		
	else if (fld[i][k] == PIAO_B)
	{
		if (isValidPos(i+1) && isValidPos(k-1) && fld[i+1][k-1] == REI_W)
			return REI_W_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k+1) && fld[i+1][k+1] == REI_W)
			return REI_W_IN_CHECK;
	}

	// avalia pecas Brancas
	else if (fld[i][k] == REI_W)
	{
		if (isValidPos(i-1) && isValidPos(k-1) && fld[i-1][k-1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i-1) && fld[i-1][k] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k+1) && fld[i-1][k+1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(k-1) && fld[i][k-1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(k+1) && fld[i][k+1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k-1) && fld[i+1][k-1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+1) && fld[i+1][k] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k+1) && fld[i+1][k+1] == REI_B)
			return REI_B_IN_CHECK;
	}
	else if (fld[i][k] == RAINHA_W)
	{
		int lin, col;
		for (lin = i-1, col = k-1; isValidPos(lin) && isValidPos(col); lin--, col--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i-1, col = k+1; isValidPos(lin) && isValidPos(col); lin--, col++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k-1; isValidPos(lin) && isValidPos(col); lin++, col--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k+1; isValidPos(lin) && isValidPos(col); lin++, col++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i-1, col = k; isValidPos(lin) && isValidPos(col); lin--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k; isValidPos(lin) && isValidPos(col); lin++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k-1; isValidPos(lin) && isValidPos(col); col--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k+1; isValidPos(lin) && isValidPos(col); col++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
	}
	else if (fld[i][k] == BISPO_W)
	{
		int lin, col;
		for (lin = i-1, col = k-1; isValidPos(lin) && isValidPos(col); lin--, col--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')
				break;
		}
		for (lin = i-1, col = k+1; isValidPos(lin) && isValidPos(col); lin--, col++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k-1; isValidPos(lin) && isValidPos(col); lin++, col--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k+1; isValidPos(lin) && isValidPos(col); lin++, col++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
	}		
	else if (fld[i][k] == TORRE_W)
	{
		int lin, col;
		for (lin = i-1, col = k; isValidPos(lin) && isValidPos(col); lin--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i+1, col = k; isValidPos(lin) && isValidPos(col); lin++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k-1; isValidPos(lin) && isValidPos(col); col--)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
		for (lin = i, col = k+1; isValidPos(lin) && isValidPos(col); col++)
		{
			if (fld[lin][col] == REI_B)
				return REI_B_IN_CHECK;
			else if (fld[lin][col] != '.')break;
		}
	}		
	else if (fld[i][k] == CAVALO_W)
	{
		int lin, col;
		if (isValidPos(i-2) && isValidPos(k-1) && fld[i-2][k-1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i-2) && isValidPos(k+1) && fld[i-2][k+1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k-2) && fld[i-1][k-2] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k+2) && fld[i-1][k+2] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k-2) && fld[i+1][k-2] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+1) && isValidPos(k+2) && fld[i+1][k+2] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+2) && isValidPos(k-1) && fld[i+2][k-1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i+2) && isValidPos(k+1) && fld[i+2][k+1] == REI_B)
			return REI_B_IN_CHECK;
	}		
	else if (fld[i][k] == PIAO_W)
	{
		if (isValidPos(i-1) && isValidPos(k-1) && fld[i-1][k-1] == REI_B)
			return REI_B_IN_CHECK;
		if (isValidPos(i-1) && isValidPos(k+1) && fld[i-1][k+1] == REI_B)
			return REI_B_IN_CHECK;
	}		
	else return NO_CHECK;
}

bool isValidPos(int pos)
{
	if (pos >= 0 && pos < 8) return true;
	else return false;
}
