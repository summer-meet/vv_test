#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#define MN 10000

using namespace std;

const int S=20;

long long factor[MN];
int fac_top;

long long muti_mod(long long a,long long b,long long c)    //返回(a*b) mod c,a,b,c<2^63
{
    a%=c,b%=c;
    long long ret=0;
    while (b)
	{
        if (b&1)
		{
            ret+=a;
            if (ret>=c) ret-=c;
        }
        a<<=1;
        if (a>=c) a-=c;
        b>>=1;
    }
    return ret;
}

long long pow_mod(long long x,long long n,long long mod)  //返回x^n mod c ,非递归版
{
    if (n==1) return x%mod;
    int bit[64],k=0;
    while (n){
        bit[k++]=n&1;
        n>>=1;
    }
    long long ret=1;
    for (k=k-1;k>=0;k--){
        ret=muti_mod(ret,ret,mod);
        if (bit[k]==1) ret=muti_mod(ret,x,mod);
    }
    return ret;
}

bool check(long long a,long long n,long long x,long long t)   //以a为基，n-1=x*2^t，检验n是不是合数
{
    long long ret=pow_mod(a,x,n),last=ret;
    for (int i=1;i<=t;i++){
        ret=muti_mod(ret,ret,n);
        if (ret==1 && last!=1 && last!=n-1) return 1;
        last=ret;
    }
    if (ret!=1) return 1;
    return 0;
}

bool Miller_Rabin(long long n)
{
    long long x=n-1,t=0,a;
    while ((x&1)==0) x>>=1,t++;
    bool flag=1;
    if (t>=1 && (x&1)==1)
	{
        for (int k=0;k<S;k++)
		{
			a=rand()%(n-1)+1;
            if (check(a,n,x,t)) {flag=1;break;}
            flag=0;
        }
    }
    if (!flag || n==2) return 1;
    return 0;
}

long long gcd(long long a,long long b)
{
    if (a==0) return 1;
    if (a<0) return gcd(-a,b);
    while (b)
	{
        long long t=a%b; a=b; b=t;
    }
    return a;
}

long long Pollard_rho(long long x,long long c)
{
    long long i=1,x0=rand()%x,y=x0,k=2,d;
    while (1)
	{
        i++;
        x0=(muti_mod(x0,x0,x)+c)%x;
        d=gcd(y-x0,x);
        if (d!=1 && d!=x) return d;
        if (y==x0) return x;
        if (i==k)
		{
            y=x0;
            k+=k;
        }
    }
}

void findfac(long long n)           //递归进行质因数分解N
{
	if (Miller_Rabin(n)){
        factor[fac_top++] = n;
        return;
    }
    long long p=n;
    while (p>=n) p=Pollard_rho(p,rand() % (n-1) +1);
    findfac(p);
    findfac(n/p);
}

int main(){
    srand(time(NULL));
	int T;
    long long in,ans;
    scanf("%d",&T);
    while (T--)
	{
        scanf("%lld",&in);
        if (Miller_Rabin(in)) printf("Prime\n");
        else{
            fac_top = 0;
            findfac(in);
            ans=in;
            for (int i = 0; i < fac_top; i++)
                ans = min(ans, factor[i]);
            printf("%lld\n",ans);
        }
    }
}
