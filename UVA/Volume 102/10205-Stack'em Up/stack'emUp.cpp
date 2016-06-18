/**************************************************************
 * Problema 10205- Stack'em Up - Programming Challenges, pag 48
 * 
 * Autor: Vinicius J. S. Souza 
 * Data:  03/07/2008
 ***************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Carta
{
	string simbolo;
	string valor;
};

void initDeck(vector<Carta> &deck);
void printDeck(vector<Carta> deck);

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int nTeste = 0;
	
	cin >> nTeste;
	//cout << nTeste << endl << endl;
	bool isInicio = true; 
	
	for (int i = 0; i < nTeste; i++)
	{
		if (!isInicio) cout << endl;
		else isInicio = false;
		vector<Carta> deck;
		initDeck(deck);
		
		int nTruques = 0;
		cin >> nTruques;
		//cout << nTruques << endl;
		int shuffle[52][nTruques];
		/** Recebe todos os truques **************/
		for (int k = 0; k < nTruques; k++)
		{
			for (int m = 0; m < 52; )
			{
				string buffer;
				getline(cin, buffer);
				istringstream is(buffer);
				
				while (is >> shuffle[m][k])
				{
					m++;
					if (m >= 52) break;
				}
			}
			/*
			for (int m = 0; m < 52; m++)
				cout << pos[m][k] << " ";
			cout << "\n\n\n\n";
			*/
		}	
		/*************************************/
		vector<int> usedTruques;
		/************ Recebe a sequencia de truques utilizados ***/
		while (true)
		{
			string input;
			getline(cin, input);
			if (input == "") break;
			int x = atoi(input.c_str());
			usedTruques.push_back(x);
		}
		
		/*************** Processa a sequencia de truques *******/
		vector<Carta> newDeck(52);						
		for (int k = 0; k < usedTruques.size(); k++)
		{
			int t = usedTruques[k]-1;
			for (int m = 0; m < 52; m++)
			{
				int x = shuffle[m][t]-1;
				//cout << "i = " << x+1 << endl;
				//cout << "j = " << m+1 << endl << endl;
				newDeck[m] = deck[x];					
			}
			deck = newDeck;
		}
		printDeck(newDeck);

	}
	return 0;
}

void initDeck(vector<Carta> &deck)
{
	string simbols[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
	string values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 13; k++)
		{
			Carta carta;
			carta.simbolo = simbols[i];
			carta.valor = values[k];
			deck.push_back(carta);
		}
	}
}

void printDeck(vector<Carta> deck)
{
	for (int i = 0; i < deck.size(); i++)
		cout << deck[i].valor << " of " << deck[i].simbolo << endl;
}
