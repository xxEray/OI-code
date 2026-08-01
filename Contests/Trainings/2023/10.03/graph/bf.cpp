// warning off
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1005,mod=1e9+7,i2=(mod+1)/2,i6=(mod+1)/6;
int n,a[N],f[N][N],ans,s1[N],s2[N],g[N],h[N],c[N<<1][N],P[N],fac[N],inv[N],s[N][N<<1];
int qpow(int a,int b=mod-2)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=(ll)ans*a%mod;
        a=(ll)a*a%mod;b>>=1;
    }
    return ans;
}
int main()
{
    scanf("%d",&n);g[0]=P[0]=h[0]=c[0][0]=fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s1[i]=s1[i-1]+(a[i]==2);
        s2[i]=s2[i-1]+(a[i]==3);
        fac[i]=(ll)fac[i-1]*i%mod;
        inv[i]=qpow(fac[i]);
        P[i]=(ll)P[i-1]*i2%mod;
        g[i]=(ll)g[i-1]*(i+i-1)%mod;
    }
    for(int i=1;i<=n+n;i++)
    {
        c[i][0]=1;
        for(int j=1;j<=min(i,n);j++)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j+j<=i;j++)
        {
            int v=(ll)c[i][j+j]*fac[j+j]%mod*inv[j]%mod;
            if((i-j)&1) h[i]=(h[i]-v+mod)%mod;
            else h[i]=(h[i]+v)%mod;
        }
    }
    if(a[1]==2) f[1][2]=i2;
    if(a[1]==3) f[1][3]=i6;
    for(int i=1;i<=n;i++)
    {
        for(int l=0;l<=n+n;l++)
        {
            if(!s[i][l]) continue;
            for(int d=(l&1);d<=min(l,n-i);d+=2)
                f[i][d]=(f[i][d]+(ll)s[i][l]*c[l][d]%mod*g[(l-d)/2])%mod;
        }
        for(int d=0;d+i<=n;d++)
        {
            if(!f[i][d]||d==0) continue;
            f[i][d]=(ll)f[i][d]*fac[d]%mod;
            int k=i+d,c1=s1[k]-s1[i],c2=s2[k]-s2[i];
            for(int l=0;l<=c2;l++)
            {
                int v=(ll)c[c2][l]*h[l]%mod*f[i][d]%mod*P[c2]%mod;
                s[k][c1+(c2-l)*2]=(s[k][c1+(c2-l)*2]+v)%mod;
            }
        }
    }
    printf("%d\n",f[n][0]);
    return 0;
}