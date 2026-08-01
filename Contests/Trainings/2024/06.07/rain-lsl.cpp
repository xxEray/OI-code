#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T> inline void read(T &x)
{
	x=0;T f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-')f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
template <typename T,typename ...Args>void read(T &x,Args&...args){read(x),read(args...);}
template <typename T> void print(T x)
{
	if(x<0) x=-x,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
}
template <typename T> void print(T x,char c){print(x); putchar(c);}
template<typename T>inline void output(T x){print(x,' ');}
template<typename T,typename ...Arg>inline void output(T x,Arg ...arg){output(x);output(arg...);}
const int N=40,M=1<<16,mod=998244353;
int n,m,a[N];
void inc(int &x,int v){x=(x+v)%mod;}
int fpow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=(ll)res*x%mod;
		y>>=1; x=(ll)x*x%mod;
	}
	return res;
}
namespace Task1
{
	int dp[N][M],f[20][20][N],C[N][N][N];
	int calcC(int x,int y)
	{
		if(x<y) return 0;
		int res=1;
		for(int i=x;i>x-y;i--)
			res=(ll)res*i%mod;
		for(int i=2;i<=y;i++)
			res=(ll)res*fpow(i,mod-2)%mod;
		return res;
	}
	void prework()
	{
		for(int i=1;i<=n;i++)
			for(int j=0;j<N;j++)
				for(int k=0;k<N;k++)
					C[i][j][k]=calcC(a[i]+j,k);
	}
	int calc(int i,int v)
	{
		int num=(i+m<=n)?(m+1):(n-i+1);
		if(a[i]<v) return 0;
		return C[i][num-1][num+v-1];
		// return _C(a[i]+num-1,num+v-1);
	}
	void solve()
	{
		dp[n+1][0]=1; prework();
		for(int i=n;i>=1;i--)
		{
			for(int i=0;i<=m;i++)
				for(int j=0;j<=i;j++)
					for(int msk=0;msk<1<<m;msk++)
						f[i][j][msk]=0;
			for(int msk=0;msk<1<<m;msk++) f[0][0][msk]=dp[i+1][msk];
			for(int j=0;j<m;j++)
				for(int k=0;k<=j;k++)
					for(int msk=0;msk<1<<m;msk++)
					{
						inc(f[j+1][k][msk],f[j][k][msk]);
						if(!((msk>>j)&1))
							inc(f[j+1][k+1][msk|1<<j],f[j][k][msk]);
					}
			for(int msk=0;msk<1<<m;msk++)
			{
				bool flg=1;
				for(int j=n-i;j<m;j++)
					if((msk>>j)&1) flg=0;
				if(!flg) continue;
				if(i+m<=n&&!((msk>>(m-1))&1)) continue;
				int nmsk=msk^((i+m<=n)?(1<<(m-1)):0);
				for(int j=0;j<=m;j++)
					for(int c=0;c<2;c++)
						inc(dp[i][nmsk<<1|c],(ll)f[m][j][msk]*calc(i,j+c)%mod);
			}
		}
		print(dp[1][(1<<m)-1],'\n');
	}
}
namespace Task2
{
	void solve()
	{

	}
}
int main()
{
	read(n,m); int tot=1;
	for(int i=1;i<=n;i++)
		read(a[i]),tot=(ll)tot*a[i]%mod;
	if(!m) return print(tot,'\n'),0;
	if(m<=16) Task1::solve();
	else Task2::solve();
	return 0;
}