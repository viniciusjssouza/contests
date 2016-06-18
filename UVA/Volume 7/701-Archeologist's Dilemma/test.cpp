#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>

using namespace std;
long double n_digits(long double n)
{
   long double i=0.0;
   while(n>=10.0)
   {
      n/=10.0;
      i+=1.0;
   }
return i;
}
int main()
{
   
   long double  n;
   while(cin>>n)
   {
   	long double i=n_digits(n);
	for(long double j=i+2.0;;j+=1.0)
      	{
		long double arg1= n;
		long double arg2=n+1.0;
		long double log2=log10(2.0);
		
		// teorema do confronto: n*10^j >= 2^E > (n+1)*10^j
		long double lower = ceil((log10(arg1)+j)/log2);
		long double upper = floor((log10(arg2)+j)/log2);
		if(upper==lower)
		{
			cout << fixed << setprecision(0) << upper << endl;	 	
			break;
		}
      }   
   }   
   return 0;
}
