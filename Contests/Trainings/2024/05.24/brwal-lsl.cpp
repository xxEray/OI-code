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
const int N=250007,inf=0x3f3f3f3f;
const ll Inf=0x3f3f3f3f3f3f3f3f;
int n,m,T,f[N],w[N],cnt,h[N]; ll c[N];
struct edge{int to,nxt;}mp[N<<1];
vector<int>vct;
void add(int x,int y)
{
	cnt++;
	mp[cnt].nxt=h[x];
	mp[cnt].to=y;
	h[x]=cnt;
}
void adde(int x,int y){add(x,y); add(y,x);}
int dis[N][85];
namespace Graph
{
	int cnt,h[N],vis[N]; edge mp[N<<1];
	void add(int x,int y)
	{
		cnt++;
		mp[cnt].nxt=h[x];
		mp[cnt].to=y;
		h[x]=cnt;
	}
	void adde(int x,int y){add(x,y); add(y,x);}
	void gen(int x,int fa)
	{
		vis[x]=1;
		for(int i=h[x];i;i=mp[i].nxt)
		{
			int y=mp[i].to;
			if(vis[y])
			{
				if(y!=fa)
				{
					::vct.push_back(x);
					::vct.push_back(y);
				}
			}
			else ::adde(x,y),gen(y,x);
		}
	}
	void BFS(int x,int k)
	{
		for(int i=1;i<=n;i++) dis[i][k]=inf;
		dis[x][k]=0; queue<int>q; q.push(x);
		while(q.size())
		{
			int x=q.front(); q.pop();
			for(int i=h[x];i;i=mp[i].nxt)
			{
				int y=mp[i].to;
				if(dis[y][k]>dis[x][k]+1)
					dis[y][k]=dis[x][k]+1,q.push(y);
			}
		}
	}
}
int siz[N],dep[N],vis[N],root,it[N],pa[N];
vector<pair<int,int>>vec[N]; ll ans[N],res[N];
vector<int>alldep[N];
void prefind(int x,int fa)
{
	siz[x]=1;
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(y==fa||vis[y]) continue;
		prefind(y,x); siz[x]+=siz[y];
	}
}
void findroot(int x,int fa,int tot)
{
	int mx=tot-siz[x];
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(y==fa||vis[y]) continue;
		findroot(y,x,tot);
		mx=max(mx,siz[y]);
	}
	if(mx<<1<=tot) root=x;
}
void work(int x,int fa,int dep,int top)
{
	vec[top].push_back({dep,x});
	alldep[x].push_back(dep);
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(y==fa||vis[y]) continue;
		work(y,x,dep+1,top);
	}
}
void solve(int x)
{
	vis[x]=1; work(x,0,0,x);
	sort(vec[x].begin(),vec[x].end());
	for(int i=h[x];i;i=mp[i].nxt)
	{
		int y=mp[i].to;
		if(vis[y]) continue;
		prefind(y,x); findroot(y,x,siz[y]);
		pa[root]=x; solve(root);
	}
}
int TTT,QQQ;
void dijkstra()
{
	priority_queue<pair<ll,int>>q;
	res[1]=0; q.push({-c[1],1}); vis[1]=1;
	while(q.size())
	{
		int x=q.top().second; q.pop();
		for(int i=alldep[x].size()-1,now=x;i>=0;i--,now=pa[now])
		{
			while(it[now]<vec[now].size()&&vec[now][it[now]].first<=f[x]-alldep[x][i])
			{
				int pos=vec[now][it[now]].second;
				TTT++;
				if(!vis[pos])
				{
					QQQ++;
					res[pos]=res[x]+c[x]; vis[pos]=1;
					q.push({-res[pos]-c[pos],pos});
				}
				it[now]++;
			}
		}
		for(int i=0;i<vct.size();i++)
		{
			int now=vct[i]; f[x]-=dis[x][i];
			for(int j=alldep[vct[i]].size()-1;j>=0;j--,now=pa[now])
			{
				while(it[now]<vec[now].size()&&vec[now][it[now]].first<=f[x]-alldep[vct[i]][j])
				{
					int pos=vec[now][it[now]].second;
					TTT++;
					if(!vis[pos])
					{
						QQQ++;
						res[pos]=res[x]+c[x]; vis[pos]=1;
						q.push({-res[pos]-c[pos],pos});
					}
					it[now]++;
				}
			}
			f[x]+=dis[x][i];
		}
	}
}
int main()
{
	freopen("brwal5.in", "r", stdin);
	freopen("brwal.out", "w", stdout);
	read(n,m,T);
	for(int i=1;i<=n;i++)
		read(f[i],c[i],w[i]);
	for(int i=1,x,y;i<=m;i++)
		read(x,y),Graph::adde(x,y);
	Graph::gen(1,0); sort(vct.begin(),vct.end());
	vct.erase(unique(vct.begin(),vct.end()),vct.end());
	for(int i=0;i<vct.size();i++) Graph::BFS(vct[i],i);
	prefind(1,0); findroot(1,0,n); solve(root);return 0;
	memset(ans,0x3f,sizeof ans);
	memset(vis,0,sizeof vis);
	memset(res,0x3f,sizeof res);
	for(int i=1;i<=n;i++) it[i]=0;
	dijkstra();
	cout<<TTT<<" "<<QQQ<<endl;
	for(int i=1;i<=n;i++)
		ans[i]=min(ans[i],res[i]);
	for(int i=1;i<=n;i++)
		c[i]+=(ll)(T-1)*w[i];
	memset(vis,0,sizeof vis);
	memset(res,0x3f,sizeof res);
	for(int i=1;i<=n;i++) it[i]=0;
	dijkstra();
	for(int i=1;i<=n;i++)
		ans[i]=min(ans[i],res[i]);
	for(int i=1;i<=n;i++)
		print(ans[i],'\n');
	return 0;
}