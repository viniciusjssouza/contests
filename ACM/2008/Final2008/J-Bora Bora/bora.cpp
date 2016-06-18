/************************************************************
* Bora Bora - Final Sul-americana 2008
*
* Autor: Vinicius J. S. Souza
* Data: 01/09/2009
* Tecnicas: estruturas de dados
************************************************************/

#include<iostream>
#include<algorithm>
#include<set>
#include<deque>
#include<vector>
#include<map>

#define jack 11
#define queen 12
#define king 13
#define ace 1

using namespace std;

class Card
{
public:
	int rank;
	char suit;
	bool effect;
	Card(int v, char s)
	{
		this->rank = v;
		this->suit = s;
		this->effect = true;
	}
};

struct CardCompare
{
	bool operator()(const Card &c1, Card const &c2)
	{
		if (c1.rank > c2.rank)
			return true;
		else if (c1.rank < c2.rank)
			return false;
		else
			return (c1.suit >= c2.suit);
	}
};

typedef multiset<Card, CardCompare> Hand;


int m, n, p;

bool tryDiscard(Hand &h, deque<Card> &discard, Card &card, Card &d)
{
	bool discarted = false;

	for (Hand::iterator ite = h.begin(); ite != h.end(); ite++)
	{
		if ((*ite).rank == card.rank || (*ite).suit == card.suit)
		{
			d = Card((*ite).rank, (*ite).suit);
			h.erase(ite);
			discarted = true;
			break;
		}
	}
	return discarted;
}

int play(int pid, deque<Hand> &game, deque<Card> &discard, deque<Card> &stock, int dir)
{
	Card card = discard.front();
	Card d(-1, '!');
	if ((card.rank == 7 || card.rank == ace) && card.effect)
	{
		int i = 0;
		if (card.rank == 1)
			i = 1;
		for (; i < 2; i++)
		{
			if (!stock.empty())
			{
				game[pid].insert(stock.front());
				stock.pop_front();
			}		
		}
		discard[0].effect = false;
	}
	else if (card.rank == jack && card.effect)
		 discard[0].effect = false;
	else if (tryDiscard(game[pid], discard, card, d) )	
		discard.push_front(d);
	else
	{
		game[pid].insert(stock.front());
		stock.pop_front();
		if (tryDiscard(game[pid], discard, card, d) )
			discard.push_front(d);				
	}
	if (game[pid].empty())	
		return pid;
	if (discard.front().rank == queen && discard.front().effect)	
	{
		dir = -dir;
		discard[0].effect = false;
	}
	
	int nextP = pid+dir;
	if (nextP >= p)
		nextP = 0;
	else if (nextP < 0)
		nextP = p-1;	
	return play(nextP, game, discard, stock, dir);
}

int main()
{
	long start = clock();
	while (true)
	{
		scanf("%d %d %d", &p, &m, &n);
		if (!n && !p && !m)
			break;
		deque<Hand> game(p, Hand());
		deque<Card> discard;
		deque<Card> stock;
		int count = 0;
		char suit;
		int rank;
		for (int i = 0; i < p; i++)
		{
			for (int k = 0; k < m; k++, count++)
			{
				scanf("%d %c", &rank, &suit);
				game[i].insert(Card(rank, suit));
			}		
		}
		scanf("%d %c", &rank, &suit);	
		discard.push_back(Card(rank,suit));
		for (count++; count < n; count++)
		{
			scanf("%d %c", &rank, &suit);	
			stock.push_back(Card(rank,suit));
		}
		int dir = 1;
		if (discard[0].rank == queen)
		{
			dir = -1;
			discard[0].effect = false;
		}

		printf("%d\n", play(0, game, discard, stock, dir) +1); 		
		
	}	
	cout << "Tempo rodando:" << ( (clock()-start) / CLOCKS_PER_SEC) << endl;	
	return 0;	
}
