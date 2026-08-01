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
const int inf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;
const double alpha=0.73;
inline void file(){
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
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
 
map<int,int> a,b,c,d;
map<pii,int> e;
map<int,bool> vis;
int n,x[500005],y[500005];
signed mian(){
    a.clear(); b.clear(); c.clear(); d.clear(); e.clear(); vis.clear();
    n=read();
    rep(i,n){
        x[i]=read(),y[i]=read();
        ++a[x[i]],++b[y[i]],++c[x[i]+y[i]],++d[x[i]-y[i]],++e[mkp(x[i],y[i])];
    }
    if(a.size()==1) return 0*puts("YES");
    rep(i,n){
        if(vis[x[i]]) continue;
        rep(j,n){
            if(x[i]==x[j]) continue;
            vis[x[i]]=1;
            if(a[x[i]]+b[y[j]]+c[x[i]+y[j]]+d[x[i]-y[j]]-3*e[mkp(x[i],y[j])]==n)
                return 0*puts("YES");
            if(a[x[i]]+b[x[j]+y[j]-x[i]]+c[x[j]+y[j]]+d[x[i]*2-x[j]-y[j]]-3*e[mkp(x[i],x[j]+y[j]-x[i])]==n)
                return 0*puts("YES");
            if(a[x[i]]+b[x[i]-(x[j]-y[j])]+c[x[i]*2-x[j]+y[j]]+d[x[j]-y[j]]-3*e[mkp(x[i],x[i]-(x[j]-y[j]))]==n)
                return 0*puts("YES");
            break;
        }
    }
    puts("NO");
    return 0;
}
signed main(){
    int _=read();
    while(_--) mian();
    return 0;
}
/*

 
*/