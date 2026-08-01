// warning off
#include<cstring>
#include<iostream>
#define ull unsigned long long
#define int long long
using namespace std;
const int P=13331;
char s[10000005];
int a[30],t1,t2,n,g[10000005];
ull p[10000005],f[10000005];
signed main()
{
    scanf("%s",s+1);
    for(int i=0;i<26;i++)scanf("%lld",&a[i]);
    scanf("%lld%lld",&t1,&t2);
    p[0]=1;
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        p[i]=p[i-1]*P;
        f[i]=f[i-1]*P+(s[i]-'a'+1);
    }
    memset(g,0x3f,sizeof(g));
    g[0]=0;
    int l=1,r=0;
    for(int i=1;i<=n;i++)
    {
        g[i]=min(g[i],g[i-1]+a[s[i]-'a']);
        while(l<=r&&l*2<i)l++;
        while(l<=r)
        {
            int r1=l,l2=l+1,r2=l*2;
            if(r2>i)r1-=r2-i,r2=i;
            if(g[l]-g[l+1]<=2*t2&&f[r1]==f[r2]-f[l2-1]*p[r2-l2+1])break;
            l++;
        }
        if(l<=r)g[i]=min(g[i],g[l]+t1+t2*(2*l-i)),printf("i=%d l=%d\n",i,l);
        r++;
    }
    printf("%lld",g[n]);
}
/*
aaaaa
3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
3 2

aaaaaaaaaaaaaa
3 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
2 2

abbbb
4 6 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
4 8

*/