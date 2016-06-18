#include<cstdio>

using namespace std;

int main() {
	int h1,m1, h2, m2, t1 = 0, t2 = 0;
	const int toMid = 60*24;
	while (true) {
		scanf("%d %d %d %d", &h1, &m1, &h2, &m2);
		if (!h1 && !h2 && !m1 && !m2)
			break;
		t1 = h1*60+m1;
		t2 = h2*60+m2;
		if (t2 < t1) {
			int r = toMid - t1;
			printf("%d\n", t2+r);
		} else
			printf("%d\n", (t2-t1));
	}
	return 0;
}