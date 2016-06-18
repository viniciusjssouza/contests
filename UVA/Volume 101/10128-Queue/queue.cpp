#include<iostream>
#include<vector>			
#include<deque>

#define MAXN 13

using namespace std;

typedef unsigned long long int64;

int p, r, n;	

inline void printSeq(const deque<int> &seq)
{
	for (int i = 0; i < seq.size(); i++)
		cout << seq[i] << ' ';
	cout << endl;
}


inline int getData(const deque<int> &seq, const int &num, int &nextLeft, int &nextRight, int &max)
{
	register int maxLeft = 0, maxRight = 0;
	register int biggerThanNum = 0;
	register int lowerThanNum = 0;
	nextLeft = nextRight = 0;
	for (register int i = 0, k = seq.size()-1; i < seq.size(); i++, k--)
	{
		if (seq[i] > maxLeft)
		{
			maxLeft = seq[i];
			nextLeft++;
		}
		if (seq[k] > maxRight)
		{
			maxRight = seq[k];
			nextRight++;
		}	
		if (seq[k] > num)
			biggerThanNum++;
		else
			lowerThanNum++;
	}
	if (num > maxLeft) 
	{
		nextLeft++;
		maxLeft = num;
	}
	if (num > seq[seq.size()-1])
		nextRight = biggerThanNum+1;
	else nextRight++;
	max = maxLeft;
	return lowerThanNum;
}

int64 backtrack(int left, int right, vector<bool> &processed, deque<int> &seq)
{
	if (left == p && right == r && seq.size() == n) 
	{	
		cout << "Contou 1:";
		printSeq(seq);
		return 1;
	}
	printSeq(seq);
	//backtrack...
	int64 subtotal = 0; 
	for (register int i = 1; i <= n; i++)
	{
		if (processed[i]) continue;

		register int nextLeft, nextRight, max;
		register int qntRight = getData(seq, i, nextLeft, nextRight, max);
		register int qntLeft = n - max;
		// inserindo a direita
		//cout << i << ":" << qntLeft << " " << qntRight << endl;
		if (qntLeft >= (p - nextLeft) &&  (r - nextRight) <= (n - seq.size() +1) &&
			nextLeft <= p && nextRight <= r)
		{ 
			vector<bool> nextProcessed = processed;
			nextProcessed[i] = true;
			deque<int> nextSeq = seq;
			nextSeq.push_back(i);
			subtotal += backtrack(nextLeft, nextRight, nextProcessed, nextSeq);
		}					
	}
	//cout << "Subtotal: " << subtotal << endl;
	return subtotal;
}


int main()
{
	vector<int64> fatorial(MAXN+1, 0);
	fatorial[0] = 1;

	int nTest;
	cin >> nTest;	
	while (nTest--)
	{
		cin >> n >> p >> r;
		int64 total = 0;
		for (int i = 1; i <= n; i++)
		{
			deque<int> seq(1, i);
			vector<bool> processed(n+1, false);
			processed[i] = true;
			total += backtrack(1, 1, processed, seq);	
		}
		cout << "Total:" << total << endl;
/*
		int resto = (n+1) - (p+r);
		if (resto && !fatorial[resto])
		{
			fatorial[resto] = 1;
			for (int i = resto; i > 0; i--)
				fatorial[resto] *= i;
		}
		cout << (total * fatorial[resto]) << endl;
*/
	}
}
