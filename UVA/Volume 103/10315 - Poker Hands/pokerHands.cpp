/***************************************************************************************
 * UVa problem 10315 - Poker Hands - Programming Challenges
 * Autor: Vinicius J. S. Souza
 * Data: 27/02/2008
 * *************************************************************************************/

#include <iostream>	
#include <string>

#define PH	5 //poker hands
#define SFLUSH		9
#define FKIND   	8
#define FHOUSE  	7
#define FLUSH   	6
#define STRAIGHT	5 
#define TKIND		4
#define TPAIR		3
#define	PAIR		2
#define	HCARD		1

using namespace std;

char cardValues[13] =
{ 
	'2', '3', '4', '5', '6', '7', '8', '9' ,'T', 'J', 'Q', 'K', 'A'
};

struct Card
{
	char value;
	char simbol;
	int rank;
};

int getCardRank(char card);
int isSFlush(Card h[PH]);
int isFKind(Card h[PH]);
int isFHouse(Card h[PH]);
int isFlush(Card h[PH]);
int isStraight(Card h[PH]);
int isTKind(Card h[PH]);
int isTPair(Card h[PH]);
int isPair(Card h[PH]);

int getHandRank(Card hand[PH]);
string tieResolver(Card b[PH], Card w[PH], int hRank);
void showInput(Card black[PH], Card white[PH]);
int sortFnc(const void* a, const void* b);

int main()
{
//	freopen("input.txt", "r", stdin);
	
	while (true)
	{
		if (feof(stdin)) return 0;		
		Card black[PH];
		Card white[PH];
		
		// recebe a entrada
		for (int i = 0; i < PH; i++)
		{
			string input;
			cin >> input;
			if (input == "") return 0;
			black[i].value = input[0];
			black[i].simbol = input[1];
			black[i].rank = getCardRank(input[0]);
		}		
		for (int i = 0; i < PH; i++)
		{
			string input;
			cin >> input;
			white[i].value = input[0];
			white[i].simbol = input[1];
			white[i].rank = getCardRank(input[0]);
		}		
		// ordena a entrada atraves dos ranks...
		qsort((void*)black, PH, sizeof(black[0]), sortFnc);
		qsort((void*)white, PH, sizeof(white[0]), sortFnc);
				
		/******** mostra a entrada *********/
		//showInput(black, white);
		
		/////// logica do negocio ////////
		int bRank = getHandRank(black);
		int wRank = getHandRank(white);
		
		if (bRank > wRank)
			cout << "Black wins.\n";
		else if (bRank < wRank)
			cout << "White wins.\n";
		else
		{
			cout << tieResolver(black, white, bRank);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////	

string tieResolver(Card b[PH], Card w[PH], int hRank)
{
	const string bwins = "Black wins.\n";
	const string wwins = "White wins.\n";
	const string tie = "Tie.\n";
	if (hRank == HCARD || hRank == FLUSH)
	{
		for (int i = 0; i < PH; i++)
		{
			if (b[i].rank > w[i].rank) return bwins;
			else if (b[i].rank < w[i].rank) return wwins;
		}
		return tie;
	}
	
	else if (hRank == PAIR)
	{
		int brank = isPair(b);
		int wrank = isPair(w);
		if (brank > wrank)
			return bwins;
		else if (brank < wrank)
			return wwins;
		else
		{
			for (int i = 0; i < PH; i++)
			{
				if (b[i].rank == brank || w[i].rank == wrank) continue;
				else if (b[i].rank > w[i].rank) return bwins;
				else if (b[i].rank < w[i].rank) return wwins;				
			}
			return tie;
		}
	}
	
	else if (hRank == TPAIR)
	{
		int bpair = 0;
		int wpair = 0;
		int bremain = -1;
		int wremain = -1;
		int i = 0;
		int k = 0;
		for (;b[i].rank != b[i+1].rank;i++)
			bremain = b[i].rank;		
		bpair = b[i].rank;
		
		for (; w[k].rank != w[k+1].rank; k++)
			wremain = w[k].rank;		
		wpair = w[i].rank;
			
		if (bpair > wpair) return bwins;
		else if (bpair < wpair) return wwins;
		else
		{
			i+=2; k+=2;
			for (;b[i].rank != b[i+1].rank;i++)
				bremain = b[i].rank;			
			bpair = b[i].rank;
			
			for (; w[k].rank != w[k+1].rank; k++)
				wremain = w[k].rank;			
			wpair = w[i].rank;
			
			if (bpair > wpair) return bwins;
			else if (bpair < wpair) return wwins;		
			else
			{
				i+=2; k+=2;
				if (bremain == -1) bremain = b[i].rank;
				if (wremain == -1) wremain = w[k].rank; 
				if (bremain > wremain) return bwins;
				else if (bremain < wremain) return wwins;
				else return tie;
			}
		}
	}
	
	else if (hRank == TKIND)
	{
		int brank = isTKind(b);
		int wrank = isTKind(w);
		if (brank > wrank)
			return bwins;
		else if (brank < wrank)
			return wwins;
		else return tie;
	}
	
	else if (hRank == FHOUSE)
	{
		int brank = isFHouse(b);
		int wrank = isFHouse(w);
		if (brank > wrank)
			return bwins;
		else if (brank < wrank)
			return wwins;
		else return tie;
	}
	
	else if (hRank == FKIND)
	{
		int brank = isFKind(b);
		int wrank = isFKind(w);
		if (brank > wrank)
			return bwins;
		else if (brank < wrank)
			return wwins;
		else return tie;
	}	
	
	else if (hRank == STRAIGHT || hRank == SFLUSH)
	{
		if (b[0].rank > w[0].rank) return bwins;
		else if (b[0].rank < w[0].rank) return wwins;
		else return tie;
	}
	
}

int isSFlush(Card h[PH])
{
	char simbol = h[4].simbol;
	for (int i = 0; i < PH-1; i++)
	{
		if (h[i].simbol == simbol && h[i].rank-1 == h[i+1].rank);
		else return false;
	}
	return 1;
}

int isFKind(Card h[PH])
{
	int limit = PH-3;
	for (int i =0; i < limit; i++)
	{
		int rank = h[i].rank;
		if (h[i+1].rank == rank && h[i+2].rank == rank && h[i+3].rank == rank)
			return rank;
	}
	return false;
}
int isFHouse(Card h[PH])
{
	int rank = h[0].rank;
	if (h[1].rank == rank && h[2].rank == rank && h[3].rank == h[4].rank)
			return rank;
	rank = h[2].rank; 
	if (h[3].rank == rank && h[4].rank == rank && h[0].rank == h[1].rank)
			return rank;	
	return false;	
}

int isFlush(Card h[PH])
{
	char simbol = h[4].simbol;
	for (int i = 0; i < PH-1; i++)
	{
		if (h[i].simbol == simbol);
		else return false;
	}
	return true;	
}

int isStraight(Card h[PH])
{
	for (int i = 0; i < PH-1; i++)
	{
		if (h[i].rank-1 == h[i+1].rank);
		else return false;
	}
	return true;	
}

int isTKind(Card h[PH])
{
	int limit = PH-2;
	for (int i =0; i < limit; i++)
	{
		int rank = h[i].rank;
		if (h[i+1].rank == rank && h[i+2].rank == rank)
			return rank;
	}
	return false;
}

int isTPair(Card h[PH])
{
	int limit = PH-1;
	int count = 0;
	for (int i =0; i < limit; i++)
	{
		int rank = h[i].rank;
		if (h[i+1].rank == rank)
		{
			count++;
			i++;
		}
		if (count >= 2) return true;
	}
	return false;	
}

int isPair(Card h[PH])
{
	int limit = PH-1;
	for (int i =0; i < limit; i++)
	{
		int rank = h[i].rank;
		if (h[i+1].rank == rank)
			return rank;
	}
	return false;	
}

int getHandRank(Card hand[PH])
{
	if (isSFlush(hand))return SFLUSH;
	else if (isFKind(hand)) return FKIND;
	else if (isFHouse(hand)) return FHOUSE;
	else if (isFlush(hand)) return FLUSH;
	else if (isStraight(hand)) return STRAIGHT;
	else if (isTKind(hand)) return TKIND;
	else if (isTPair(hand)) return TPAIR;
	else if (isPair(hand)) return PAIR;
	else return HCARD;
}

int getCardRank(char card)
{
	for (int i = 0; i < 13; i++)
	{
		if (card == cardValues[i]) return i+2;
	}	
	return -1;
}

void showInput(Card black[PH], Card white[PH])
{
	cout << "---- Black ----\n";
	for (int i = 0; i < PH; i++)
	{
		cout << black[i].value << "  " << black[i].simbol << "  " << black[i].rank << endl;
	}
	cout << "\n---- White ----\n";
	for (int i = 0; i < PH; i++)
	{
		cout << white[i].value << "  "  << white[i].simbol << "  " << white[i].rank << endl;
	}	
}

int sortFnc(const void* a, const void* b)
{
	Card* x = (Card*)a;
	Card* y = (Card*)b;
	if (x->rank > y->rank) return -1;
	else if (x->rank < y->rank) return 1;
	else return 0;
}