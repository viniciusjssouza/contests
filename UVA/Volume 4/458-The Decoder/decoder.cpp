#include<iostream>

using namespace std;

int main() {
	int dif=  'i' - 'p';
	char c;
	while (!feof(stdin) && (c = getchar()) != EOF) {
		if (c == '\n')
			putchar('\n');
		else printf("%c", c+dif);		
	}
}
