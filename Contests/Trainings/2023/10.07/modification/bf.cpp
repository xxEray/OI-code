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
int a[300005],f[2][2005][5],g[2005][2005],s[2][300005];
int ask(int o,int l,int r){
	if(l>r)return 0;
	return s[o][r]-s[o][l-1];
}
signed main(){
	int n=read();
	for(int i=1;i<=n;i++)scanf("%1lld",&a[i]);
	for(int i=1;i<=n;i++){
		for(int o=0;o<2;o++){
			s[o][i]=s[o][i-1]+(a[i]==o);
		}
	}
	for(int i=1;i<=n;i++){
		int val=-inf;
		for(int j=i;j<=n;j++){
			val=max(val,s[0][j]-s[1][j]);
			g[i][j]=max(g[i][j],val-s[0][i-1]+s[1][j]);
		}
	}
	for(int i=1;i<=n;i++){
		f[1][i][0]=max(ask(0,1,i),ask(1,1,i)),f[1][i][1]=g[1][i];
	}
	printf("%lld ",max(f[1][n][0],f[1][n][1]));
	for(int j=2;j<=n;j++){
		int o=j&1ll;
		for(int i=1;i<=n;i++){
			f[o][i][0]=f[o][i][1]=-inf;
			for(int k=1;k<i;k++){
				f[o][i][0]=max(f[o][i][0],f[o^1][k][0]+ask(0,k+1,i));
				f[o][i][0]=max(f[o][i][0],f[o^1][k][0]+ask(1,k+1,i));
				f[o][i][1]=max(f[o][i][1],f[o^1][k][0]+g[k+1][i]);
				f[o][i][1]=max(f[o][i][1],f[o^1][k][1]+ask(0,k+1,i));
				f[o][i][1]=max(f[o][i][1],f[o^1][k][1]+ask(1,k+1,i));
			}
			f[o][i][0]=max(f[o][i][0],f[o^1][i][0]);
			f[o][i][1]=max(f[o][i][1],f[o^1][i][1]);
		}
		printf("%lld ",max(f[o][n][0],f[o][n][1]));
		if(max({f[o][n][0],f[o][n][1]})==n){
			for(int k=j+1;k<=n;k++)printf("%lld ",n);
			return 0;
		}
	}
	return 0;
}
