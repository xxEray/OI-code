#include<bits/stdc++.h>
using namespace std;
char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template<typename T>inline void read(T &x)
{
	x=0; T f=0; char c=getchar();
	while(!isdigit(c)){f|=(c=='-');c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	if(f) x=-x;
}
template<typename T,typename ...Arg>inline void read(T &x,Arg &...arg){read(x);read(arg...);}
template<typename T>inline void print(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar((x%10)^48);
}
template<typename T>inline void print(T x,char c){print(x);putchar(c);}
const int N=100007,siz1=1200,siz2=70;
int n,m,q,a[N],ans[N],t[N],num,link[N],res[N],pos[N];
int solve(int x)
{
	memset(t,0,sizeof t); int p=1,ret=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		while(t[a[p]]<x) t[a[p]]++,p=p==n?1:p+1;
		link[i]=p; t[a[i]]--;
	}
	for(int i=n;i>=1;i--)
	{
		if(link[i]<i) res[i]=1,pos[i]=link[i];
		else res[i]=res[link[i]]+1,pos[i]=pos[link[i]];
	}
	for(int i=1;i<=link[1];i++)
	{
		if(pos[i]>=i) ret=min(ret,res[i]);
		else ret=min(ret,res[i]+1);
	}
	return ret;
}
void solve0()
{
	for(int i=1;i<m;i++) ans[i]=solve(i);
	for(int i=m;i<=n;i++) ans[i]=1;
	for(int i=1,x;i<=q;i++)
		read(x),print(ans[x],'\n');
}
int main()
{
	read(n,q);
	for(int i=1;i<=n;i++) read(a[i]),t[a[i]]++;
	for(int i=1;i<=n;i++) m=max(m,t[i]);
	if(m<=siz1) return solve0(),0;
	for(int i=1;i<=siz1;i++) ans[i]=solve(i);
	int lst=siz1;
	for(int i=siz2;i>1;i--)
	{
		int ml=1,mr=m-1,mid,res=lst;
		while(ml<=mr)
		{
			mid=(ml+mr)>>1;
			if(solve(mid)>=i) res=mid,ml=mid+1;
			else mr=mid-1;
		}
		for(int j=lst+1;j<=res;j++) ans[j]=i;
		lst=res;
	}
	for(int i=lst+1;i<=n;i++) ans[i]=1;
	for(int i=1,x;i<=q;i++) read(x),print(ans[x],'\n');
	return 0;
}