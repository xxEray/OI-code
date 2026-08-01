#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void()
#endif
using namespace std;
typedef pair<int,int>pii;
const int inf=1e15;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,k,a[100005],b[100005],o[100005];vector<int>v;set<pii>s;
int check(int mid){
	int base=0,sum=0;s.clear(),v.clear();
	for(int i=1;i<=n;i++){
		base+=b[i];
		if(!o[i])s.insert({a[i]-b[i],i}),sum+=a[i]-b[i];
		while(base+sum>mid){
			if(s.empty())return 0;
			sum-=(*s.rbegin()).fi,s.erase(prev(s.end()));
		}
		while(base<0){
			if(s.empty()){base=0;break;}
			pii u=*s.begin();sum-=u.fi;s.erase(u);
			if(base+u.fi<0)base+=u.fi,v.push_back(u.se);
			else u.fi+=base,base=0,s.insert(u),sum+=u.fi;
		}
	}
	for(auto x:s)v.push_back(x.se);
	return ((int)v.size()>=k);
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	int cnt=0,all=0;
	for(int i=1;i<=n;i++)if(a[i]<b[i])cnt++;
	if(cnt>k){k=n-k,all=1;for(int i=1;i<=n;i++)swap(a[i],b[i]);}
	for(int i=1;i<=n;i++)if(a[i]<b[i])k--,swap(a[i],b[i]),o[i]=1;
	int l=0,r=inf,res=inf;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);assert(check(res));
	for(int i=0;i<k;i++)o[v[i]]=1;
	for(int i=1;i<=n;i++)putchar((o[i]^all)?'A':'B');
	return 0;
}
