#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 50500
#define M 50500

using namespace std;

struct Q
{
	int l,r,id,ans;
} que[M];

int in[N],b[N],last[N],_div[N];
int top,n,q;

bool by_r(Q a, Q b)
{
	return a.r<b.r;
}

bool by_id(Q a, Q b)
{
	return a.id<b.id;
}

int lowbit(int x)
{
	return x&(-x);
}

void add(int x,int delta)
{
	while (x)
	{
		b[x]=max(b[x],delta);
		x-=lowbit(x);
	}
}

int query(int x)
{
	int ret=0;
	while (x<=n)
	{
		ret=max(ret,b[x]);
		x+=lowbit(x);
	}
	return ret;
}

void pdiv(int x)
{
	top=0;
	int j;
	for (j=1;j*j<x;j++)
	{
		if (x%j==0) _div[++top]=j,_div[++top]=x/j;
	}
	if (j*j==x) _div[++top]=j;
}

void init()
{
	memset(last,0,sizeof last);
	memset(b,0,sizeof b);
}

int main()
{
	int T,k;
	scanf("%d",&T);
	while (T--)
	{
		init();
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&in[i]);
		scanf("%d",&q);
		for (int i=0;i<q;i++)
		{
			scanf("%d%d",&que[i].l,&que[i].r);
			que[i].id=i;
		}
		sort(que,que+q,by_r);
		int rr=0;
		for (int i=1;i<=n;i++)
		{
			pdiv(in[i]);

			for (;top;top--)
			{
				k=_div[top];
				if (last[k]) add(last[k],k);
				last[k]=i;
			}
			while (que[rr].r==i && rr<q)
			{
				que[rr].ans=query(que[rr].l);
				rr++;
			}
		}

		sort(que,que+q,by_id);
		for (int i=0;i<q;i++)
			printf("%d\n",que[i].ans);
	}
	return 0;
}
