#include<cstdio>
#include<algorithm>
using namespace std;
#define N 1060000
int n,k,a,b,v[N],vl[N],T,as;
struct orzzh{
	int s1[N*2],s2[N],h1,t1,h2,t2;
	void init(){h1=h2=1;t1=t2=0;}
	void ins(int x){if(t1<h1||vl[s1[t1]]>vl[x]||(vl[s1[t1]]==vl[x]&&s1[t1]>x))s1[++t1]=x;else s2[++t2]=x;}
	int getmn()
	{
		if(h1>t1){int as=s2[t2--];return as;}
		if(h2>t2){int as=s1[t1--];return as;}
		if(vl[s1[t1]]<vl[s2[t2]]||(vl[s1[t1]]==vl[s2[t2]]&&s1[t1]<s2[t2])){int as=s1[t1--];return as;}
		else {int as=s2[t2--];return as;}
	}
	int getmx()
	{
		if(h1>t1){int as=s2[h2++];return as;}
		if(h2>t2){int as=s1[h1++];return as;}
		if(vl[s1[h1]]>vl[s2[h2]]||(vl[s1[h1]]==vl[s2[h2]]&&s1[h1]>s2[h2])){int as=s1[h1++];return as;}
		else {int as=s2[h2++];return as;}
	}
}sth;
pair<int,int> doit(int n)
{
	int s1=sth.getmn(),s2=sth.getmx();
	vl[s2]-=vl[s1];
	if(n==2){as=1;return make_pair(vl[s1],s1);}
	sth.ins(s2);
	int f1=vl[s1],f2=vl[s2];
	pair<int,int> v4=doit(n-1);
	pair<int,int> v1=make_pair(f1,s1),v3=make_pair(f2,s2);
	if(v4<v3){as++;return v4<v1?v1:v4;}
	else{as=0;return make_pair(0,0);}
}
int solve()
{
	sth.init();
	for(int i=1;i<=n;i++)vl[i]=v[i];
	for(int i=n;i>=1;i--)sth.ins(i);
	doit(n);
	return n-as;
}
int main()
{
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		if(t==1)
		{
			scanf("%d",&n);
			for(int i=1;i<=n;i++)scanf("%d",&v[i]);
		}
		else
		{
			scanf("%d",&k);
			for(int i=1;i<=k;i++)scanf("%d%d",&a,&b),v[a]=b;
		}
		printf("%d\n",solve());
	}
}
