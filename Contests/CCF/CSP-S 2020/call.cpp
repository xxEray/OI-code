#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
#define N 105000
#define mod 998244353
int n,m,a,b,c,v[N],dp1[N],dp2[N],st[N],s[N][3],ind[N],ct;
vector<int> sn[N],nt[N];
int main()
{
	freopen("call.in","r",stdin);
	freopen("call.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a==1)scanf("%d",&c),s[i][0]=a,s[i][1]=b,s[i][2]=c;
		else if(a==2)s[i][0]=a,s[i][1]=b;
		else
		{
			s[i][0]=a;s[i][1]=b;
			for(int j=1;j<=b;j++)scanf("%d",&c),sn[i].push_back(c),nt[c].push_back(i),ind[i]++;
		}
	}
	scanf("%d",&b);s[m+1][0]=3;s[m+1][1]=b;
	for(int i=1;i<=b;i++)scanf("%d",&c),sn[m+1].push_back(c),nt[c].push_back(m+1),ind[m+1]++;
	queue<int> fu;
	for(int i=1;i<=m+1;i++)if(!ind[i])fu.push(i);
	while(!fu.empty())
	{
		int s1=fu.front();fu.pop();
		st[++ct]=s1;
		for(int i=0;i<nt[s1].size();i++)
		{
			int tp=nt[s1][i];
			ind[tp]--;if(!ind[tp])fu.push(tp);
		}
	}
	for(int i=1;i<=m+1;i++)
	{
		int x=st[i];
		if(s[x][0]==1)dp1[x]=1;
		else if(s[x][0]==2)dp1[x]=s[x][1];
		else
		{
			dp1[x]=1;
			for(int j=0;j<sn[x].size();j++)dp1[x]=1ll*dp1[x]*dp1[sn[x][j]]%mod;
		}
	}
	for(int i=1;i<=n;i++)v[i]=1ll*v[i]*dp1[m+1]%mod;
	dp2[m+1]=1;
	for(int i=m+1;i>=1;i--)
	{
		int x=st[i];
		if(s[x][0]==1)v[s[x][1]]=(v[s[x][1]]+1ll*s[x][2]*dp2[x])%mod;
		else if(s[x][0]==3)
		{
			int st=dp2[x];
			for(int j=(int)sn[x].size()-1;j>=0;j--)dp2[sn[x][j]]=(dp2[sn[x][j]]+st)%mod,st=1ll*st*dp1[sn[x][j]]%mod;
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",v[i]);
}
