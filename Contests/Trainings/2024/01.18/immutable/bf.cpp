// 	author:LGM_Joanna_

#include <bits/stdc++.h>
#define marry return
//#define int long long
#define lowbit(x) (x&-x)
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<48||ch>57)f=ch=='-'?-1:1,ch=getchar();
	while(ch>=48&&ch<=57)x=x*10+(ch^48),ch=getchar();
	return x*f;}
using namespace std;

const int inf=1e9;
const int F=0;
const int mod=114514;

int n;
int h[500001],B[500001];
int mn[2000001];
#define mid  ((l+r)>>1)
#define b1 (b<<1)
#define b2 (b<<1|1)
inline void build(int l,int r,int b)
{
	if(l==r)
		marry mn[b]=h[l],B[l]=b,void();
	build(l,mid,b1);
	build(mid+1,r,b2);
	mn[b]=min(mn[b1],mn[b2]);
}
inline int query(int l,int r,int b,int ll,int rr)
{
	if(l>=ll&&r<=rr)
		marry mn[b];
	int res=inf;
	if(mid>=ll)
		res=min(res,query(l,mid,b1,ll,rr));
	if(mid<rr)
		res=min(res,query(mid+1,r,b2,ll,rr));
	marry res;
}
struct node{
	int nx,to;
}w[1000001];
int head[500001],t;
inline void add(int a,int b) {	w[++t]={head[a],b},head[a]=t;	}
set<int>mp[500001];
int top,hi[500001],cnt[500001];
long long ans=0;
inline int init(int l,int r)
{
	int num=query(1,n,1,l,r),now=l,k=++top;
	auto p=mp[num].lower_bound(l);	
	hi[k]=num,cnt[k]=r-l+1;
	ans=max(ans,1ll*hi[k]*cnt[k]);
	
//	printf("%d %d %d %d\n",l,r,hi[k],cnt[k]);
	if(l==r)
		marry k;
	for(;p!=mp[num].end()&&(*p)<=r;++p)
	{
		if((*p)>now)
			add(k,init(now,(*p)-1));
		now=(*p)+1;
	}
	if(now<=r)
		add(k,init(now,r));
	
	marry k;
}

long long X[500001],Y[500001];
int T;
inline void addnum(long long  xx,long long yy)
{
	while(T>1&&(yy-Y[T])*(X[T]-X[T-1])>=(Y[T]-Y[T-1])*(xx-X[T]))
		--T;
	X[++T]=xx,Y[T]=yy;
}
struct convex{
	vector<long long>x,y;
	int top,ch=0;
	inline void merge(convex &s)
	{
		if(top==0)
		{
			top=s.top;
			x=s.x,y=s.y;
			marry;
		}
		int l=0,r=0;
		T=0;
		
		while(l<top||r<s.top)
		{
			if(l==top)
				addnum(s.x[r],s.y[r]),++r;
			else if(r==s.top)
				addnum(x[l],y[l]),++l;
			else if(x[l]>=s.x[r])
				addnum(s.x[r],s.y[r]),++r;
			else if(x[l]<s.x[r])
				addnum(x[l],y[l]),++l;
		}
		top=T;
		for(int i=1;i<=T;++i)
			x[i-1]=X[i],
			y[i-1]=Y[i];
	}
	inline long long query(long long k)
	{
		while(ch<top-1&&x[ch+1]*k+y[ch+1]>=x[ch]*k+y[ch])
			++ch;
		while(ch>0&&x[ch-1]*k+y[ch-1]>=x[ch]*k+y[ch])
			--ch;
		marry x[ch]*k+y[ch];
	}
	inline void init(int siz)
	{
		x.resize(siz+1);
		y.resize(siz+1);
	}
	inline void print()
	{
		for(int i=0;i<top;++i)
			printf("%lld %lld  ",x[i],y[i]);
	}
};
struct seg{
	convex c[2000001];
	inline void build(int l,int r,int b)
	{
		if(l==r)
			marry;
		build(l,mid,b1);
		build(mid+1,r,b2);
		c[b]=c[b1];
		c[b].init(c[b].top+c[b2].top+1);
		c[b].merge(c[b2]);
//		printf("%d %d   ",l,r);
//		c[b].print();
//		puts("");
	}
	inline long long query(int l,int r,int b,int ll,int rr,long long k)
	{
		if(l>=ll&&r<=rr)
			marry c[b].query(k);
		long long res=0;
		if(mid>=ll)
			res=max(res,query(l,mid,b1,ll,rr,k));
		if(mid<rr)
			res=max(res,query(mid+1,r,b2,ll,rr,k));
		marry res;
	}
}T1,T2;

int dfn[500001],dfnr[500001],p[500001];
inline void dfs(int s)
{
	dfn[s]=++top;
	p[top]=s;
	T1.c[B[top]].x.push_back(-cnt[s]);
	T1.c[B[top]].y.push_back(1ll*cnt[s]*hi[s]);
	T1.c[B[top]].top=1;
	for(int i=head[s];i;i=w[i].nx)
	{
		int vi=w[i].to;
		dfs(vi);
	}
	dfnr[s]=top;
}

int bg[500001],xd[500001];
inline void dfs2(int s)
{
	bg[s]=s;
	int fi=0,se=0;
	long long mx=0;
	for(int i=head[s];i;i=w[i].nx)
	{
		int vi=w[i].to;
		dfs2(vi);
		mx=max(mx,T1.query(1,n,1,dfn[vi],dfnr[vi],hi[s]));
		
		if(1ll*hi[bg[vi]]*cnt[bg[vi]]>1ll*hi[bg[s]]*cnt[bg[s]])
			bg[s]=bg[vi];
		int now=bg[vi];
		if(fi==0||1ll*hi[now]*cnt[now]>1ll*hi[fi]*cnt[fi])
			swap(fi,now);
		if(se==0||1ll*hi[now]*cnt[now]>1ll*hi[se]*cnt[se])
			swap(se,now);
	}
	ans=max(ans,mx+1ll*hi[s]*cnt[s]);
	ans=max(ans,1ll*hi[fi]*cnt[fi]+1ll*hi[se]*cnt[se]); 
	xd[s]=max(mx+1ll*hi[s]*cnt[s],1ll*hi[fi]*cnt[fi]+1ll*hi[se]*cnt[se]);
	if(se)
		T2.c[B[dfn[s]]].x.push_back(-cnt[fi]-cnt[se]),
		T2.c[B[dfn[s]]].y.push_back(1ll*hi[fi]*cnt[fi]+1ll*hi[se]*cnt[se]),
		++T2.c[B[dfn[s]]].top;
		
	T2.c[B[dfn[s]]].x.push_back(-cnt[s]);
	T2.c[B[dfn[s]]].y.push_back(1ll*cnt[s]*hi[s]+mx);
	++T2.c[B[dfn[s]]].top;
	
	if(se&&-cnt[fi]-cnt[se]<cnt[s])
		swap(T2.c[B[dfn[s]]].x[0],T2.c[B[dfn[s]]].x[1]),
		swap(T2.c[B[dfn[s]]].y[0],T2.c[B[dfn[s]]].y[1]);
}

inline void dfs3(int s)
{
	long long fi=0,se=0;
	
	for(int i=head[s];i;i=w[i].nx)
	{
		int vi=w[i].to;
		dfs3(vi);
		ans=max(ans,1ll*hi[s]*cnt[s]+T2.query(1,n,1,dfn[vi],dfnr[vi],hi[s]));
		long long now=T1.query(1,n,1,dfn[vi],dfnr[vi],hi[s]);
		if(fi==0||now>=fi)
			swap(now,fi);
		if(se==0||now>=se)
			swap(now,se);
	}
	ans=max(ans,1ll*cnt[s]*hi[s]+fi+se);
}
inline void dfs4(int s)
{
	int mx=0,se=0;
	for(int i=head[s];i;i=w[i].nx)
	{
		int vi=w[i].to;
		dfs4(vi);
		int now=bg[vi];
		if(mx==0||1ll*hi[mx]*cnt[mx]<1ll*hi[now]*cnt[now])
			swap(now,mx);
		
		if(se==0||1ll*hi[se]*cnt[se]<1ll*hi[now]*cnt[now])
			swap(now,se);
	}
	for(int i=head[s];i;i=w[i].nx)
	{
		int vi=w[i].to;
		if(vi==mx)
			ans=max(ans,xd[vi]+1ll*hi[se]*cnt[se]);
		else
			ans=max(ans,xd[vi]+1ll*hi[mx]*cnt[mx]);
	}
	
}


signed main()
{
//	freopen("immutable5.in","r",stdin);
//	freopen("immutable.out","w", stdout);
	
	n=read();
	for(int i=1;i<=n;++i)
	{
		h[i]=read();
		mp[h[i]].insert(i);
	}
	build(1,n,1);
	init(1,n);
	printf("%lld ",ans);
	top=0;
	dfs(1);
	T1.build(1,n,1);
	dfs2(1);
	printf("%lld ",ans);
	T2.build(1,n,1),
	dfs3(1);
	dfs4(1);
	printf("%lld\n",ans);
	
	marry F;
}

