#include <iostream>
#include <list>

using namespace std;

#define TRUE    1
#define FALSE   0
#define LEFT    0
#define RIGHT   1

int N;
int S1, S2, S3, S4, S;
int T1, T2, T3, T4, T;
int F1, F2, F3, F4, F;
int forbidden [10000];
int g[10000][8];
int steps[10000];


void cleanUp() {
    for (int i = 0; i < 10000; i++) {
        forbidden[i] = FALSE;
        steps[i] = -1;
    }
}

int nextConfig (int state, int button, int direction) {
    int digit, order, toAdd;

    if (button == 1) order = 1000;
    else if (button == 2) order = 100;
    else if (button == 3) order = 10;
    else if (button == 4) order = 1;

    digit = (state % (order * 10)) / order;

    if (direction == RIGHT) {
        toAdd = -1 * order;
        if (digit == 0) toAdd = 9 * order;
    }
    else {
        toAdd = 1 * order;
        if (digit == 9) toAdd = -9 * order;
    }

    return (state + toAdd);
}


void buildGraph() {
    for (int i = 0; i < 10000; i++) {
        g[i][0] = nextConfig(i, 1, LEFT);
        g[i][1] = nextConfig(i, 1, RIGHT);

        g[i][2] = nextConfig(i, 2, LEFT);
        g[i][3] = nextConfig(i, 2, RIGHT);

        g[i][4] = nextConfig(i, 3, LEFT);
        g[i][5] = nextConfig(i, 3, RIGHT);

        g[i][6] = nextConfig(i, 4, LEFT);
        g[i][7] = nextConfig(i, 4, RIGHT);
    }
}


void readData() {
    cin >> S1 >> S2 >> S3 >> S4;
    S = (S1 * 1000) + (S2 * 100) + (S3 * 10) + S4;

    cin >> T1 >> T2 >> T3 >> T4;
    T = (T1 * 1000) + (T2 * 100) + (T3 * 10) + T4;

    int n;  //  no of forbidden configurations

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> F1 >> F2 >> F3 >> F4;
        F = (F1 * 1000) + (F2 * 100) + (F3 * 10) + F4;
        forbidden[F] = TRUE;
    }
}

int traverseG() {
    list <int> L;   //  queue to hold configurations
    list <int> :: iterator i;
    int currentConfig, neighbour;

    if (forbidden[T] || forbidden[S]) return -1;
    if (S == T) return 0;

    L.push_back(S);
    steps[S] = 0;

    for (i = L.begin(); L.size() > 0; i++) {
        currentConfig = *i;
        L.pop_front();

        for (int j = 0; j < 8; j++) {
            neighbour = g[currentConfig][j];
            //if (neighbour == T)
            //    return steps[currentConfig] + 1;

            if (!forbidden [neighbour] && steps[neighbour] == -1) {
                steps[neighbour] = steps[currentConfig] + 1;
                if (neighbour == T) return steps[neighbour];

                L.push_back(neighbour);
            }
        }
    }

    //  not found
    return -1;
}


int main() {

    long start = clock();
    cin >> N;

    buildGraph();

    for (int i = 0; i < N; i++) {
        cleanUp();
        readData();
        cout << traverseG() << endl;
    }
    cout << "Fim: " << (clock()-start) << endl;

    return 0;
}
