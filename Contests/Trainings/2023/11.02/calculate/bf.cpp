// warning off
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int inf=1e18;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[200005],mex[5005][5005],c[200005],s[200005],f[200005];
signed main(){
	int n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[i]=s[i-1]+a[i];
	if(n<=5000){
		for(int i=1;i<=n;i++){
			for(int j=0;j<=n;j++)c[j]=0;
			for(int j=i;j<=n;j++){
				c[a[j]]++,mex[i][j]=mex[i][j-1];
				while(c[mex[i][j]])mex[i][j]++;
			}
		}
		for(int i=1;i<=n;i++){
			f[i]=-inf;
			for(int j=i-1;j>=max(0ll,i-m);j--){
				f[i]=max(f[i],f[j]+mex[j+1][i]*(s[i]-s[j]));
			}
			// printf("f[%lld] = %lld\n", i, f[i]);
		}
		printf("%lld\n",f[n]);
		return 0;
	}
	int ans=0;
	for(int i=1;i<=n;i+=m){
		int j=max(n,i+m-1);map<int,int>mp;
		for(int k=i;k<=j;k++)mp[a[k]]++;
		int mex=0;while(mp[mex])mex++;
		ans+=(s[j]-s[i-1])*mex;
	}
	printf("%lld\n",ans);
	return 0;
}