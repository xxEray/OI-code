#include<bits/stdc++.h>
using namespace std;
int n,m,a[500003],k1,k2,k3,k4,k5,k6,k7,k8,k9,F[500003]; 
int v[500003][2];
vector<int>E[500003];
void merge(int X){
	v[X][0]=a[X]*2;
	v[X][1]=a[X];
	for(auto i:E[X]){
		if(i==F[X])continue;
		v[X][0]=max(v[X][0],v[i][0]);
		v[X][0]=max(v[X][0],v[X][1]+v[i][1]+1);
		v[X][1]=max(v[X][1],v[i][1]+1);
	}
	return;
}
void dfs(int now){
	for(auto i:E[now]){
		if(i==F[now])continue;
		F[i]=now;
		dfs(i);
	}
	merge(now);
	return;
}
int main(){
	freopen("award.in", "r", stdin);
	freopen("award.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		cin>>k1>>k2;
		E[k1].emplace_back(k2);
		E[k2].emplace_back(k1);
	}
	dfs(1);
	cin>>m;
	while(m--){
		cin>>k1>>k2;
		a[k1]=k2;
		while(k1){
			merge(k1);
			k1=F[k1];
		}
		cout<<(v[1][0]+1)/2<<endl;
	}
	return 0;
}