#include<bits/stdc++.h>
using namespace std;
int n,ls[501000],rs[500100],sta[500100],top,sz[501000],dfn[501000],bel[501000];
int lp[501000],rp[501000];
#define ll long long
#define pb push_back
ll h[501000],md[500100],nt[501000];
void dfs(int x){
	if(!x)return;
	bel[dfn[x]=++dfn[0]]=x;
	if(ls[x])lp[ls[x]]=lp[x],rp[ls[x]]=x-1,dfs(ls[x]);
	if(rs[x])lp[rs[x]]=x+1,rp[rs[x]]=rp[x],dfs(rs[x]);
	md[x]=max(md[ls[x]],md[rs[x]]);
	sz[x]=sz[ls[x]]+sz[rs[x]]+1;
	nt[x]=h[x]*(rp[x]-lp[x]+1);
	md[x]=max(md[x],nt[x]);
}
struct no{
	ll x,y;
	no(){}
	no(ll x_,ll y_){x=x_,y=y_;}
	no operator - (const no &a) const{
		return no(x-a.x,y-a.y);
	}
	bool operator < (const no &a) const{
		if(x!=a.x)return x<a.x;
		return y<a.y;
	}
	inline ll F(ll a){return a*x+y;}
};
vector<no>gr[2001000];
bool cro(no a,no b){return (__int128)a.x*b.y>=(__int128)a.y*b.x;}
bool ck(no a,no b,no c){return cro(b-a,c-a);}
void ig(int p,no z){
	int sz=gr[p].size();
	if(sz--&&gr[p].back().x==z.x){
		if(gr[p].back().y>=z.y)return;
		gr[p].pop_back();
	}
	while(sz>=2&&ck(gr[p][sz-2],gr[p][sz-1],z))sz--,gr[p].pop_back();
	gr[p].pb(z);
}
void up(int p,int l,int r,int x,no z){
	if(x==r)return ig(p,z);
	int mid=(l+r)>>1;
	if(x<=mid)up(p<<1,l,mid,x,z);
	else ig(p<<1,z),up(p<<1|1,mid+1,r,x,z);
}
int be[2010000];
const ll I=1e18;
ll ask(int p,ll x){
	if(gr[p].empty())return -I;int o=be[p];
	while(o+1<gr[p].size()&&gr[p][o].F(x)<=gr[p][o+1].F(x))o++;
	be[p]=o;return gr[p][o].F(x);
}
void build(int p,int l,int r){
	//(h[x]-h[i])(rp[x]-lp[x]+1)+h[i](rp[i]-lp[i]+1)
	if(l==r){int X=bel[l];ig(p,no(rp[X]-lp[X]+1,nt[X]));return;}
	int mid=(l+r)>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	int sl=gr[p<<1].size(),sr=gr[p<<1|1].size(),i=0,j=0;
	while(i<sl||j<sr){
		if(i<sl&&(j==sr||gr[p<<1][i].x<gr[p<<1|1][j].x))ig(p,gr[p<<1][i++]);
		else ig(p,gr[p<<1|1][j++]);
	}
}
int pl,pr;ll pz,fz;
void as(int p,int l,int r){
	if(pl<=l&&r<=pr){fz=max(fz,ask(p,pz));return;}
	int mid=(l+r)>>1;
	if(pl<=mid)as(p<<1,l,mid);if(pr>mid)as(p<<1|1,mid+1,r);
}
int main(){
	// freopen("immutable.in","r",stdin);
	// freopen("immutable.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&h[i]);
	for(int i=1;i<=n;i++){
		int ntop=top;
		while(top&&h[sta[top]]>=h[i])top--;
		if(top)rs[sta[top]]=i;
		if(ntop!=top)ls[i]=sta[top+1];
		sta[++top]=i;
	}
	int rt=sta[1];lp[rt]=1,rp[rt]=n,dfs(rt);
	build(1,1,n);
	ll f1=md[rt],f2=f1,f3=0;
	for(int i=n;i;i--){
		int x=bel[i];
		f2=max(f2,md[ls[x]]+md[rs[x]]);
		if(sz[x]>1)fz=-I,pl=dfn[x]+1,pr=dfn[x]+sz[x]-1,pz=-h[x],as(1,1,n),f2=max(f2,fz+nt[x]);
	}
	printf("%lld %lld\n",f1,f2);
	return 0;
}
