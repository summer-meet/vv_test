#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1001000

using namespace std;

bool su[N];
int in,i;

void shai()
{
	int p;
	memset(su,1,sizeof su);
	su[1]=0;
	for (int i=2;i*i<N;i++)
		if (su[i])
		{
			p=i*i;
			while (p<N)
			{
				su[p]=0;
				p+=i;
			}
		}
}

int main()
{
	shai();

	while (scanf("%d",&in),in)
	{
		for (i=3;i<=in/2;i+=2)
			if (su[i] && su[in-i]) break;
		if (i==in/2+1) printf("Goldbach's conjecture is wrong.\n");
		else printf("%d = %d + %d\n",in,i,in-i);
	}

	return 0;
}

