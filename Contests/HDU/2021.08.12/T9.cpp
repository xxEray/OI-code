#include<bits/stdc++.h>
using namespace std;
int T,n;
char c[100010];
int ans[3000010],pr[3000010];
int cn,ch[3000010][26];
void cl(int x){
    pr[x]=-1e9;ans[x]=0;
    for(int i=0;i<26;i++)ch[x][i]=0;
}
int main(){
    scanf("%d",&T);
    while(T--){
        cl(cn=1);
        scanf("%s",c+1);n=strlen(c+1);
        for(int i=1;i<=n;i++){
            int u=1;
            for(int j=0;j<30&&i+j<=n;j++){
                int p=c[i+j]-'a';
                if(!ch[u][p])cl(ch[u][p]=++cn);
                u=ch[u][p];
                if(i-pr[u]>j+1)pr[u]=i,ans[u]++;
            }
        }
        int q;scanf("%d",&q);
        while(q--){
            scanf("%s",c);int u=1,l=strlen(c);
            for(int j=0;j<l;j++)u=ch[u][c[j]-'a'];
            printf("%d\n",ans[u]);
        }
    }
    return 0;
}