#include<iostream>
#include<cmath>

using namespace std;

const double EPS = 1e-10;

inline int cmp(double x, double y = 0, double tol = EPS) 
{
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

inline double dist(double x1, double y1, double x2, double y2)
{
	return sqrt(( pow((x1-x2), 2.0) + pow((y1-y2), 2.0) ));
}

int N;
double input[1010][2];

int main()
{
	while (!feof(stdin)	&& scanf("%d", &N) == 1)
	{
		double dx, dy, gx, gy;
		scanf("%lf %lf %lf %lf", &gx, &gy, &dx, &dy);
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &input[i][0], &input[i][1]);
		int index = -1;
		for (int i = 0; i < N; i++)
		{
			double dogDist = ((dist(dx,dy,input[i][0], input[i][1])) / 2.0);
			double golpherDist = dist(gx,gy,input[i][0], input[i][1]);
			if (cmp(dogDist, golpherDist) > 0)
			{
				index = i;
				break;
			}
		}	
		if (index < 0)
			printf("The gopher cannot escape.\n");
		else
			printf("The gopher can escape through the hole at (%.3lf,%.3lf).\n", 
				input[index][0], input[index][1]);			 		
	}
	return 0;
}
