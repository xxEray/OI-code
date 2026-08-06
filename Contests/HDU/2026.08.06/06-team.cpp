// auto input
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<array>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define DE(fmt,...) fprintf(stderr, "Line %d : " fmt "\n",__LINE__,##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pll>vpll;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
namespace Poly{
	const int T=21;//2^T>n+m
	const int N=(1<<T)+10;
	int inv[N],fac[N];
	int w[T][(1<<(T-1))+10],iw[T][(1<<(T-1))+10];
	int p[N];
	void prework(){
		fac[0]=1;
		for(int i=1;i<=(1<<T);i++)fac[i]=1ll*fac[i-1]*i%mod;
		inv[1<<T]=qpow(fac[1<<T],mod-2);
		for(int i=(1<<T)-1;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
		for(int i=0;i<T;i++){
			int n=1<<(i+1);
			int W=qpow(3,(mod-1)/n);
			int IW=qpow(332748118,(mod-1)/n);
			w[i][0]=1;
			iw[i][0]=1;
			for(int j=1;j<n/2;j++)w[i][j]=1ll*w[i][j-1]*W%mod,iw[i][j]=1ll*iw[i][j-1]*IW%mod;
		}
	}
	void NTT(int *a,int n,int type){
		for(int i=0;i<n;i++)
			if(i<p[i])
				swap(a[i],a[p[i]]);
		for(int i=1,c=0;i<n;i<<=1,++c){
			for(int j=0;j<n;j+=i<<1){
				for(int k=0;k<i;++k){
					int u=a[j+k],v=1ll*a[j+i+k]*(type==1?w[c][k]:iw[c][k])%mod;
					a[j+k]=add(u,v);
					a[j+i+k]=del(u,v);
				}
			}
		}
		if(type==-1){
			int inv=qpow(n,mod-2);
			for(int i=0;i<n;++i)a[i]=1ll*a[i]*inv%mod;
		}
	}
	void MUL(int *f,int *g,int *h,int n,int m){//f[n], g[m], h[4n]
		int len=1,ct=0;
		while(len<=n+m-2)len<<=1,++ct;
		int a[len],b[len];
		memset(a,0,sizeof(int)*len);memset(b,0,sizeof(int)*len);
		memcpy(a,f,sizeof(int)*n);
		memcpy(b,g,sizeof(int)*n);
		for(int i=0;i<len;i++)p[i]=(p[i>>1]>>1)|((i&1)<<(ct-1));
		NTT(a,n,1);
		NTT(b,n,1);
		for(int i=0;i<n;i++)h[i]=1ll*a[i]*b[i]%mod;
		NTT(h,n,-1);
	}
}
struct poly{
	vi a;
	poly(){}
	int size(){return a.size();}
	void resize(int x){a.resize(x);}
	int &operator[](const int &i){
		if(i>=a.size()){
			dpi(i,a.size());
		}
		return a[i];
	}
	void print(){for(auto i:a)cout << i << ' ';puts("");}
	poly &operator+=(poly &b){
		int n=max((int)a.size(),b.size());
		a.resize(n);
		for(int i=0;i<n;i++)cadd(a[i],b[i]);
		return *this;
	}
	poly &operator-=(poly &b){
		int n=max((int)a.size(),b.size());a.resize(n);
		for(int i=0;i<n;i++)cdel(a[i],b[i]);
		return *this;
	}
	poly &operator*=(poly &b){
		int n=a.size(),m=b.size();
		if(n<5||m<5){
			poly c;c.resize(n+m-1);
			for(int i=0;i<n;i++)if(a[i])
				for(int j=0;j<m;j++)if(b[j])
					cadd(c[i+j],1ll*a[i]*b[j]%mod);
			*this=c; 
			return *this;
		}
		int f[n],g[m],h[n+m];
        copy(a.begin(),a.end(),f);
		copy(b.a.begin(),b.a.end(),g);
		Poly::MUL(f,g,h,n,m);
		a.resize(n+m-1);for(int i=0;i<n+m-1;i++)a[i]=h[i];
		return *this;
	}
};
poly operator+(poly &a,poly &b){poly t=a;return t+=b;}
poly operator-(poly &a,poly &b){poly t=a;return t-=b;}
poly operator*(poly &a,poly &b){poly t=a;return t*=b;}
const int N=500010;
int n,vis[N],phi[N],fac[N],inv[N];
vi pr;
void init(){
	phi[1]=1;n=500000;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;--i)inv[i]=1ll*(i+1)*inv[i+1]%mod;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pr.pb(i);
			phi[i]=i-1;
		}
		for(auto j:pr){
			if(i*j>n)break;
			vis[i*j]=1;
			if(i%j==0){
				phi[i*j]=phi[i]*j;
				break;
			}
			phi[i*j]=phi[i]*(j-1);
		}
	}
}
int f[N],g[N],h[N];
void solve(){
	read(n);
	for(int d=1;d<=n;d++)
		for(int k=d;k<=n;k+=d)
			cadd(f[k],1ll*phi[d]*(k/d)%mod);
	for(int d=1;d<=n;d++){
		dbg(d);
		poly f,g;
		//m = n/d
		// b + m - (b-a) = m + a
		int m=n/d;
		dbg(m);
		f.resize(m+1);
		g.resize(m+1);
		for(int i=0;i<=m;i++){
			if(i)f[i]=fac[i*d];
			g[i]=fac[(m-i)*d];
		}
		f*=g;
		for(int a=1;a<=m;a++){
			dbg(m+a);
			dbg(f.a.size());
			int w=f[m+a];
			w=1ll*w*phi[d]%mod*inv[a*d]%mod;
			cadd(g[a*d],w);
		}

		// for(int a=1;a<=n/d;a++){
		// 	h[a]=0;
		// 	for(int b=a;b<=n/d;b++){
		// 		cadd(h[a],1ll*fac[b*d]*inv[(b-a)*d]%mod);
		// 	}
		// 	h[a]=1ll*h[a]*phi[d]%mod*inv[a*d]%mod;
		// 	cadd(g[a*d],h[a]);
		// }
	}
	int ans=0;
	for(int k=1;k<=n;k++){
		// dpi(f[k],g[k]);
		cadd(ans,1ll*f[k]*g[k]%mod);
	}
	cout<<ans<<'\n';
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	init();
	Poly::prework();
    int T;read(T);
    while(T--)solve();
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
} /*
1
5
*/