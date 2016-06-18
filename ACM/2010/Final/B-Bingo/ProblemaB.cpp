#include <stdio.h>
#include <vector>

using namespace std;

int main(){
    int n,b;
    while(true){
       scanf("%d %d",&n,&b);
       if(!n && !b)
          break;
       vector<bool> numbers(n+1,false);
       vector<int> balls(b);
       for(int i=0; i<b; i++){
          scanf("%d",&balls[i]);
          for(int j=i; j>0; j--)
             numbers[abs(balls[i]-balls[j])]=true;
       }
       bool ok=true;
       for(int i=0; i<=n; i++)
          if(!numbers[i]){
             ok=false;
             break;
          }
       if(ok)
          printf("Y\n");
       else
          printf("N\n");
    }
}
