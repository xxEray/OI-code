#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
char c[N];
namespace GG{
int sa[N],tr[N<<2],rk[N<<2],t[N],h[N],st[N][20],lg[N],n_;
int lcp(int x,int y){
    if(x==y)return n_-x+1;
    x=rk[x],y=rk[y];if(x>y)swap(x,y);x++;int k=lg[y-x+1];
    return min(st[x][k],st[y-(1<<k)+1][k]);
}
void SA(int n){
    n_=n;
    lg[0]=-1;
    for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
    int m=128;
    for(int i=1;i<=n;i++)t[rk[i]=c[i]]++;
    for(int i=1;i<=m;i++)t[i]+=t[i-1];
    for(int i=n;i;i--)sa[t[rk[i]]--]=i;
    for(int k=1;;k<<=1){
        int o=0;
        for(int i=n-k+1;i<=n;i++)tr[++o]=i;
        for(int i=1;i<=n;i++)if(sa[i]>k)tr[++o]=sa[i]-k;
        for(int i=1;i<=m;i++)t[i]=0;
        for(int i=1;i<=n;i++)t[rk[i]]++;
        for(int i=1;i<=m;i++)t[i]+=t[i-1];
        for(int i=n;i;i--)sa[t[rk[tr[i]]]--]=tr[i];
        swap(tr,rk);
        rk[sa[1]]=o=1;
        for(int i=2;i<=n;i++)
            rk[sa[i]]=(tr[sa[i-1]]==tr[sa[i]]&&tr[sa[i-1]+k]==tr[sa[i]+k])?o:(++o);
        if(o==n)break;m=o;
    }
    for(int i=1,k=0;i<=n;i++){
        if(k)k--;
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&c[i+k]==c[j+k])k++;
        h[rk[i]]=st[rk[i]][0]=k;
    }
    for(int j=1;j<20;j++)for(int i=1;i+(1<<j)-1<=n;i++)
        st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
}
#define pi pair<int,int>
int R[N],e,ch[N][26],cn,tp[N],ry[N],f[N];
int no[N],nc,rk[N],no2[N],rk2[N];
int sgn(int l1,int r1,int l2,int r2){
    r1=r1-l1+1,r2=r2-l2+1;int xp=1;
    if(r1>r2)xp=-1,swap(r1,r2),swap(l1,l2);
    int lc=GG::lcp(l1,l2);
    if(lc<r1)return (c[l1+lc]<c[l2+lc])?xp:-xp;
    if(r1!=r2){
        lc=GG::lcp(l2,l2+r1);
        if(lc<r2-r1)return (c[l2+lc]<c[l2+r1+lc])?xp:-xp;
    }
    lc=GG::lcp(l2+(r2-r1),l1);
    if(lc<r1)return (c[l2+(r2-r1)+lc]<c[l1+lc])?xp:-xp;
    return 0;
}
#define ll long long
ll C3(ll x){return x*(x-1)*(x-2)/6;}
ll C2(ll x){return x*(x-1)/2;}
void dfs(int x){
    if(ry[x])no2[++nc]=x,rk2[x]=nc;
    for(int i=0;i<26;i++)if(ch[x][i])
        dfs(ch[x][i]);
}
bool chk2(int cl,int cr,int bl,int br){
    cr=cr-cl+1,br=br-bl+1;
    int lc=GG::lcp(cl,bl);
    if(lc<min(cr,br))return c[cl+lc]<c[bl+lc];
    return cr<br;
}
int gt(int pl,int pr){
    int l=1,r=nc,kr=r+1;
    while(l<=r){
        int mid=(l+r)>>1,u=ry[no2[mid]];
        if(chk2(pl,pr,R[u-1]+1,R[u]))
            kr=mid,r=mid-1;
        else l=mid+1;
    }
    return kr;
}
bool chk(int cl,int cr,int al,int ar,int bl,int br){
    cr=cr-cl+1,ar=ar-al+1,br=br-bl+1;
    int lc=GG::lcp(cl,al);
    if(cr>ar){
        if(lc<ar)return c[cl+lc]<c[al+lc];
        cl+=ar,cr-=ar;
    }
    else{
        if(lc<cr)return c[cl+lc]<c[al+lc];
        return 1;
    }
    lc=GG::lcp(cl,bl);
    if(lc<min(cr,br))return c[cl+lc]<c[bl+lc];
    return cr<br;
}
int gt2(int u,int v){
    int al=R[u-1]+1,ar=R[u],bl=R[v-1]+1,br=R[v];
    int l=1,r=nc,kl=0;
    while(l<=r){
        int mid=(l+r)>>1,z=ry[no2[mid]],cl=R[z-1]+1,cr=R[z];
        if(chk(cl,cr,al,ar,bl,br))kl=mid,l=mid+1;
        else r=mid-1;
    }
    return kl;
}
struct BIT{
    ll tr[301000];
    inline void ad(int x,ll z){
        for(;x<=nc;x+=(x&-x))tr[x]+=z;
    }
    inline ll ask(int x){
        ll s=0;
        for(;x;x-=(x&-x))s+=tr[x];
        return s;
    }
}T;
#define pb push_back
vector<pair<ll,pair<int,int> > >G[N];
int main(){
    scanf("%d",&e);
    cn=1;
    for(int i=1;i<=e;i++){
        scanf("%s",c+R[i-1]+1);
        R[i]=strlen(c+R[i-1]+1);
        R[i]+=R[i-1];
        int u=1;
        for(int j=R[i-1]+1;j<=R[i];j++){
            int p=c[j]-'a';
            if(!ch[u][p])ch[u][p]=++cn,f[cn]=u;
            u=ch[u][p];
        }
        tp[u]++,ry[u]=i;
    }
    dfs(1);
    GG::SA(R[e]);
    for(int i=1;i<=nc;i++)no[i]=no2[i];
    sort(no+1,no+nc+1,[&](int x,int y){
        int a=ry[x],b=ry[y];
        int ct=sgn(R[a-1]+1,R[a],R[b-1]+1,R[b]);
        if(ct!=0)return ct>0;
        return x<y;
    });
    for(int i=1;i<=nc;i++)rk[no[i]]=i;
    ll ans=0;
    for(int i=1;i<=nc;i++){
        int u=no[i],v=u,cl=R[ry[u]-1]+1,cr=R[ry[u]];
        ans+=C3(tp[u]);
        while(v){
            if(!ry[v]){v=f[v];continue;}
            int lv=R[ry[v]]-R[ry[v]-1],zl=1;
            if(u!=v)zl=gt(cl+lv,cr);
            int r=min(rk[u],rk[v]);
            if(u!=v&&zl<=((rk[u]<rk[v])?rk2[u]:rk2[v])){
                if(rk[u]<rk[v])ans+=C2(tp[u])*tp[v];
                else ans+=C2(tp[v])*tp[u];
            }
            if(r>1){
                r--;
                ll kz=((u==v)?C2(tp[u]):(1ll*tp[u]*tp[v]));
                int zr=gt2(((rk[u]<rk[v])?ry[v]:ry[u]),((rk[u]<rk[v])?ry[u]:ry[v]));
                if(zl<=zr)
                G[r].pb({kz,{zl,zr}});
                /*for(int j=1;j<=r;j++)
                if(rk2[no[j]]<=zr&&rk2[no[j]]>=zl)ans+=kz*tp[no[j]];*/
            }
            v=f[v];
        }
    }
    for(int i=1;i<=nc;i++){
        T.ad(rk2[no[i]],tp[no[i]]);
        for(auto it:G[i])ans+=(T.ask(it.second.second)-T.ask(it.second.first-1))*it.first;
    }
    printf("%lld\n",ans);
    return 0;
}