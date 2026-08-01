#include<bits/stdc++.h>
const int mxn=20;
using namespace std;
#define int ll
#define ll long long
int n;ll hp;
ll w[mxn],len[mxn];
vector<ll>d[mxn],pres[mxn];
ll t[1<<mxn],ssm;
ll dp[1<<mxn];
inline bool check(int tt){
	for(int i=0;i<(1<<n);++i)dp[i]=0;
	for(int msk=0;msk<(1<<n);++msk){
		int tf=t[msk];
		if(dp[msk]>=hp)return 1;
		if(tf>tt)continue;
		for(int i=0;i<n;++i)if(!(msk&(1<<i))){
			int tmsk=msk|(1<<i);
			if(tf+len[i]-1>tt)dp[tmsk]=max(dp[tmsk],dp[msk]+pres[i][tt-tf]);
			else dp[tmsk]=max(dp[tmsk],dp[msk]+pres[i][len[i]-1]);
		}
	}
    for(int i=0;i<(1<<n);++i)if(dp[i]>=hp)return 1;
	return 0;
}
inline void solve(){
	ssm=0;
	cin>>n>>hp;
	for(int i=0;i<n;++i){
		cin>>w[i]>>len[i];
		d[i].clear();pres[i].clear();
		for(ll x,j=0;j<len[i];++j)cin>>x,d[i].push_back(x),ssm+=x;
		ll sm=0;
		for(int j=0;j<len[i];++j)sm+=d[i][j],pres[i].push_back(sm);
	}
	for(int msk=0;msk<(1<<n);++msk){
		t[msk]=0;
		for(int i=0;i<n;++i)if(msk&(1<<i))t[msk]+=w[i];
	}
//	if(ssm<hp){
//		cout<<-1<<endl;
//		return;
//	}
	ll lo=0,hi=500000000,md;
	for(;lo<hi;){
		md=(lo+hi)/2;
		if(check(md))hi=md;
		else lo=md+1;
	}
	if(hi>=500000000)hi=-1;
	cout<<hi<<endl;
}
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	for(;T--;)solve();
	return 0;
}