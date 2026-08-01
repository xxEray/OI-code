#ifdef DEBUG
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#endif
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
int n,M;
LL MOD,jc[203],ans[203],S[203][203];
int ny[1000003],f[203],dp[203];
signed main(){
#ifdef DEBUG
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n>>M>>MOD;
	jc[0]=1;
	for(int i=1;i<=200;i++)jc[i]=jc[i-1]*i%MOD;
	ny[1]=1;
	for(int i=2;i<=1000000;i++)ny[i]=(MOD-MOD/i)*ny[MOD%i]%MOD;
#ifdef DEBUG
	fprintf(stderr,"clock=%lu\n",clock());
#endif
	f[0]=1;
	for(int i=0;i<n;i++){
		int m=std::min(i+1,M);
		#pragma GCC unroll(16)
		for(int j=0;j<=m;j++)dp[j]=(LL)f[j]*ny[n-i+j]%MOD;
		#pragma GCC unroll(16)
		for(int j=1;j<=m;j++)f[j]=(LL)(dp[j-1]+dp[j])*(n-i)%MOD;
		f[0]=(LL)dp[0]*(n-i)%MOD;
	}
#ifdef DEBUG
	fprintf(stderr,"clock=%lu\n",clock());
#endif
	S[0][0]=1;
	for(int i=1;i<=M;i++){
		for(int j=1;j<=i;j++)S[i][j]=(S[i-1][j-1]+S[i-1][j]*j)%MOD;
	}
	for(int i=1;i<=M;i++){
		for(int j=0;j<=i;j++)ans[i]=(ans[i]+jc[j]*(S[i][j]*f[j]%MOD))%MOD;
	}
	for(int i=1;i<=M;i++)cout<<ans[i]<<endl;
#ifdef DEBUG
	fprintf(stderr,"clock=%lu\n",clock());
#endif
	return 0;
}