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
const int N=2000007; const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m,a[N],mx[N],dep[N],top[N],pa[N],son[N];
int dfx,dfn[N],rdfn[N],epos[N]; ll ans;
vector<int>E[N];
struct segment_tree
{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	ll f[N<<2];
	void update(int rt,int l,int r,int p,ll x)
	{
		if(l==r) return f[rt]=x,void();
		int mid=(l+r)>>1;
		if(p<=mid) update(ls,l,mid,p,x);
		else update(rs,mid+1,r,p,x);
		f[rt]=max(f[ls],f[rs]);
	}
	ll ask(int rt,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return f[rt];
		int mid=(l+r)>>1; ll res=0;
		if(L<=mid) res=max(res,ask(ls,l,mid,L,R));
		if(R>mid) res=max(res,ask(rs,mid+1,r,L,R));
		return res;
	}
	#undef ls
	#undef rs
}seg;
struct DSU
{
	int fa[N]; int &operator[](int x)&{return fa[x];}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
}dsu;
int ch[N<<1][2],siz[N<<1],fa[N<<1],idx; ll res[N<<1],val[N<<1];
struct Splay
{
	#define ls (ch[x][0])
	#define rs (ch[x][1])
	int root;
	Splay(){siz[root=++idx]=1; res[idx]=val[idx]=-inf;}
	int sontype(int x){return x==ch[fa[x]][1];}
	void pushup(int x)
	{
		res[x]=max(res[ls],res[rs]);
		res[x]=max(res[x],val[x]);
		siz[x]=siz[ls]+siz[rs]+1;
	}
	void pushup(){pushup(root);}
	void rotate(int x)
	{
		int pa=fa[x],ga=fa[pa],T=sontype(x);
		if(ga) ch[ga][sontype(pa)]=x;
		if(ch[x][T^1]) fa[ch[x][T^1]]=pa;
		fa[x]=ga; ch[pa][T]=ch[x][T^1];
		ch[x][T^1]=pa; fa[pa]=x;
		pushup(pa); pushup(x);
	}
	void splay(int x,int pos=0)
	{
		// cout<<"!!!"<<endl;
		for(int fx;(fx=fa[x])!=pos;rotate(x))
			if(fa[fx]!=pos) rotate(sontype(x)==sontype(fx)?fx:x);
		if(!pos) root=x;
		// cout<<"???"<<endl;
	}
	void output(int x)
	{
		cout<<x<<" "<<ls<<" "<<rs<<" "<<val[x]<<" "<<res[x]<<" "<<siz[x]<<endl;
		if(ls) output(ls);
		if(rs) output(rs);
	}
	void insert(ll v)
	{
		assert(!ch[root][1]);
		ch[root][1]=++idx;
		val[idx]=res[idx]=v;
		siz[idx]=1; fa[idx]=root;
		pushup(); splay(idx);
	}
	bool find(int k)
	{
		int res=-1,x=root; k++;
		while(x)
		{
			if(k<=siz[ls]) x=ls;
			else
			{
				k-=siz[ls];
				if(k==1){res=x;break;}
				k--; x=rs;
			}
		}
		if(res==-1) return false;
		return splay(res),true;
	}
	int Find(int k)
	{
		int res=-1,x=root; k++;
		while(x)
		{
			if(k<=siz[ls]) x=ls;
			else
			{
				k-=siz[ls];
				if(k==1){res=x;break;}
				k--; x=rs;
			}
		}
		return res;
	}
	bool erase(int k)
	{
		if(!find(k-1)) return false;
		int P=Find(k+1);
		// output(root);
		if(P!=-1)
		{
			splay(P,root);
			// puts("!!!!!!!!!!");
			// output(root);
			// puts("!!!!!!!!!!");
			ch[ch[root][1]][0]=0;
			pushup(ch[root][1]);
		}
		else ch[root][1]=0;
		return pushup(),true;
	}
	void getnew()
	{
		find(siz[root]-1);
		fa[ch[root][1]=++idx]=root;
		siz[idx]=1; val[idx]=res[idx]=0;
		pushup(); splay(idx);
	}
	ll askl(){return res[ch[root][0]];}
	ll askr(){return res[ch[root][1]];}
}Tr[N>>1];
void prework(int x)
{
	mx[x]=dep[x]=dep[pa[x]]+1;
	for(auto y:E[x])
	{
		prework(y);
		if(mx[y]>mx[x])
			mx[x]=mx[y],son[x]=y;
	}
}
void work(int x,int ntop)
{
	top[x]=ntop;
	rdfn[dfn[x]=++dfx]=x;
	Tr[ntop].insert(a[x]);
	if(son[x]) work(son[x],ntop);
	for(auto y:E[x])
		if(y!=son[x]) work(y,y);
	epos[x]=dfx;
}
void upload(int x)
{
	seg.update(1,1,n,dfn[x],res[Tr[x].root]);
	if(siz[Tr[x].root]==1) dsu[dfn[x]]=dfn[x]+1;
}
void update(int x)
{
	int T=top[x],D=dep[x]-dep[T]+1;
	if(!Tr[T].find(D)) return ;
	Tr[T].erase(D); upload(T);
	for(int i=dsu.find(dfn[x]+1);i<=epos[x];i=dsu.find(i+1))
	{
		int id=rdfn[i]; Tr[id].find(1);
		ll V=val[Tr[id].root];
		Tr[id].erase(1); upload(id);
		int fx=pa[id],fd=dep[fx]-dep[top[fx]]+1;
		if(siz[Tr[top[fx]].root]<=fd)
			Tr[top[fx]].getnew();
		Tr[top[fx]].find(fd);
		val[Tr[top[fx]].root]+=V;
		Tr[top[fx]].pushup();
		upload(top[fx]);
	}
}
ll ask(int x)
{
	ll res=seg.ask(1,1,n,dfn[x],epos[x]);
	int T=top[x],D=dep[x]-dep[T]+1;
	if(Tr[T].find(D-1))
		res=max(res,Tr[T].askr());
	return res;
}
int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	// freopen("lsl.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=2,x;i<=n;i++)
		read(x),E[pa[i]=x].push_back(i);
	prework(1); work(1,1);
	for(int i=1;i<=n;i++)
		if(top[i]==i) upload(i);
	for(int i=1;i<=n;i++)
		if(top[i]==i) dsu[dfn[i]]=dfn[i];
		else dsu[dfn[i]]=dfn[i]+1;
	// for(int i=1;i<=n;i++)
	// 	cout<<top[i]<<" ";
	// puts("");
	dsu[n+1]=n+1;
	for(ll i=1,opt,x;i<=m;i++)
	{
		read(opt,x);
		// x^=ans;
		if(opt==2) update(x);
		else print(ans=ask(x),'\n');
		// puts(">>>>>>>>>>");
		// Tr[1].output(Tr[1].root);
		// puts(">>>>>>>>>>");
	}
	return 0;
}
/*
7 3
14 20 7 3 5 7 12 
1 2 3 1 3 5 
2 4
2 3
1 3
*/