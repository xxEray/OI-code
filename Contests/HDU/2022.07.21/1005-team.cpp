//Was yea ra,rra yea ra synk sphilar yor en me exec hymme METAFALICA waath!
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define ull unsigned ll
#define lowbit(x) (x&(-x))
#define djq 998244353
const double eps=1e-8;
const short sint=0x3f3f;
const int inf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;
const double alpha=0.73;
inline void file(){
	freopen("mayuri.in","r",stdin);
	freopen("mayuri.out","w",stdout);
}
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<20)+5,stdin),p1==p2)?EOF:*p1++;
}
//#define getc getchar
inline ll read(){
	rg ll ret=0,f=0;char ch=getc();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getc();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getc();}
    return f?-ret:ret;
}
#define epb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define it iterator
#define mkp make_pair
#define naive return 0*puts("YES")
#define angry return 0*puts("NO")
#define fls fflush(stdout)
#define rep(i,a) for(rg int i=1;i<=a;++i)
#define per(i,a) for(rg int i=a;i;--i)
typedef vector<int> vec;
typedef pair<int,int> pii;
struct point{ int x,y; point(int x=0,int y=0):x(x),y(y) {} inline bool operator<(const point& T)const{ return x^T.x?x<T.x:y<T.y; }; };
inline int ksm(int base,int p){int ret=1;while(p){if(p&1)ret=1ll*ret*base%djq;base=1ll*base*base%djq,p>>=1;}return ret;}
inline void pls(int& x,const int k){ x=(x+k>=djq?x+k-djq:x+k); }
inline int add(const int a,const int b){ return a+b>=djq?a+b-djq:a+b; }
inline void sub(int& x,const int k){ x=(x-k<0?x-k+djq:x-k); }

int lgn,dp[100005],sf[100005];
int n,m,a[100005],b[100005];
int g[100005][19],f[100005][19];
vec p[100005];
pii w[100005];
inline int qg(int l,int r){
	const int lgl=log2(r-l+1);
	return min(g[l][lgl],g[r-(1<<lgl)+1][lgl]);
}
inline int qf(int l,int r){
	const int lgl=log2(r-l+1);
	return min(f[l][lgl],f[r-(1<<lgl)+1][lgl]);
}
inline int findg(int x,int lim){
	if(x==1) return 1;
	if(g[x-1][0]<lim) return x;
	int l=1,r=x-1,mid;
	while(l<r) mid=l+r>>1,((qg(mid,x-1)>=lim)?(r=mid):(l=mid+1));
	return r;
}
inline int findf(int x,int lim){
	if(x==n) return n;
	if(f[x+1][0]<lim) return x;
	int l=x+1,r=n,mid;
	while(l<r) mid=(l+r+1)>>1,((qf(x+1,mid)>=lim)?(l=mid):(r=mid-1));
	return l;
}
signed mian(){
	n=read(),m=read(); g[n][0]=f[1][0]=0; lgn=log2(n);
	rep(i,n) a[i]=read(),b[i]=read(),p[i].clear();
	rep(i,n-1) g[i][0]=a[i+1]-b[i];
	for(rg int i=2;i<=n;++i) f[i][0]=a[i-1]-b[i];
	for(rg int j=1;j<=lgn;++j)
        for(rg int i=1;i<=n-(1<<j)+1;++i)
    		f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]),
    		g[i][j]=min(g[i][j-1],g[i+(1<<(j-1))][j-1]);
    rep(i,m){
    	int x=read(),L=read(),R=read();
    	//p[findf(x,R)].epb(findg(x,L));
    	//printf("%d %d\n",findf(x,R),findg(x,L));
    	//p[findg(x,L)].epb(findf(x,R));
    	w[i]=mkp(findg(x,L),findf(x,R));
    }
    sort(w+1,w+1+m); int _m=1;
    for(rg int i=2;i<=m;++i) if(w[i].se>w[_m].se) w[++_m]=w[i];
    int tot=m-_m; m=_m; dp[0]=sf[0]=1;
	rep(i,m) p[w[i].se].epb(w[i].fi);
    rep(i,n){
    	sort(all(p[i])); dp[i]=0;
    	for(int l:p[i])
			if(l>1) pls(dp[i],(sf[i-1]-sf[l-2]+djq)%djq);
			else pls(dp[i],sf[i-1]);
		sf[i]=add(sf[i-1],dp[i]);
    }
    int ans=1ll*dp[n]*ksm(2,tot)%djq;
    printf("%d\n",ans);
	return 0;
}
signed main(){
	int _=read();
	while(_--) mian();
	return 0;
}