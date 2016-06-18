#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int pos[101][2];

long table[20][20];

int n;

int k;

int bw;

long count1;

bool isValid(int level, int x, int y) {
   int b1 = y - x;
   int b2 = x + y;
   for (int i = 0; i < level; i++) {
      int b = pos[i][0] - pos[i][1];
      if (b1 == b)
         return false;
      b = pos[i][1] + pos[i][0];
      if (b2 == b)
         return false;
   }
   return true;
}

int m[30][30];

void countSols(int level) {
   if (level >= k) {
      count1++;
   } else {
      int pt = (pos[level - 1][0] * n) + pos[level - 1][1];
      int li = -1;
      for (int p = pt; p < n * n; p += 2) {
         int i = p / n;
         int j = p % n;
         if (li != -1 && n % 2 == 0) {
            if (i > li) {
               if (i % 2 == bw)
                  p++;
               else
                  p--;
               i = p / n;
               j = p % n;
            }
         }
         if (isValid(level, j, i) && p > pt) {
            pos[level][0] = i;
            pos[level][1] = j;
            m[i][j] = 1;
            countSols(level + 1);
            m[i][j] = 0;
         }
         li = i;
      }
   }
}

int main() {
   cin>>n;
   cin>>k;
   for(int i=0; i<20; i++) {
      for(int j=0; j<20; j++) {
         table[i][j] = -1;
      }
   }
   while (n>0 || k>0) {
      if (k == 0) {
         if (n == 0)
            break;
         cout<<1<<endl;
      } else if (n == 1) {
         if (k == 1)
            cout<<1<<endl;
      } else {
         if (k > 2 * (n - 1)) {
            cout<<0<<endl;
         } else {
            count1 = 0;
            if(table[n][k]>-1) {
               count1 = table[n][k];
            }
            else {
            if (n % 2 == 0) {
               int tk = k;
               long cuenta[80];
               long cuenta2[80];
               cuenta[0] = 1;
               cuenta2[0] = 1;
               for (k = 1; k <= tk; k++) {
                  count1 = 0;
                  bw = 1;
                  int li = -1;
                  for (int p = 0; p < n * n; p += 2) {
                     int i = p / n;
                     int j = p % n;
                     if (li != -1) {
                        if (i > li) {
                           if (i % 2 == bw)
                              p++;
                           else
                              p--;
                           i = p / n;
                           j = p % n;
                        }
                     }
                     pos[0][0] = i;
                     pos[0][1] = j;
                     m[i][j] = 1;
                     countSols(1);
                     m[i][j] = 0;
                     li = i;
                  }
                  cuenta[k] = count1;
               }
               count1 = 0;
               for (int i = 0; i <= tk; i++) {
                  count1 += (cuenta[i] * cuenta[tk - i]);
               }
            } else {
               int tk = k;
               long cuenta[80];
               long cuenta2[80];
               cuenta[0] = 1;
               cuenta2[0] = 1;
               for (k = 1; k <= tk; k++) {
                  count1 = 0;
                  bw = 1;
                  for (int p = 0; p < n * n; p += 2) {
                     int i = p / n;
                     int j = p % n;
                     pos[0][0] = i;
                     pos[0][1] = j;
                     m[i][j] = 1;
                     countSols(1);
                     m[i][j] = 0;
                  }
                  cuenta[k] = count1;
                  count1 = 0;
                  bw = 0;
                  for (int p = 1; p < n * n; p += 2) {
                     int i = p / n;
                     int j = p % n;
                     pos[0][0] = i;
                     pos[0][1] = j;
                     m[i][j] = 1;
                     countSols(1);
                     m[i][j] = 0;
                  }
                  cuenta2[k] = count1;
               }
               count1 = 0;
               for (int i = 0; i <= tk; i++) {
                  count1 += (cuenta[i] * cuenta2[tk - i]);
               }
            }
            table[n][k] = count1;
            }
            cout<<count1<<endl;
         }
      }
      n = 0;
      k = 0;
      cin>>n;
      cin>>k;
   }
}
