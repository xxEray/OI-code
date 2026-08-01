#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n, K;
int a[N], b[N];
int ia[N], ib[N];

int cnt[N];
bool vis[N];

int mx;
void solve() {
	for(int i = 1; i <= n; i++) ia[i] = ib[i] = cnt[i] = 0;
	for(int i = 1; i <= K; i++) ia[a[i]] = i;
	for(int i = 1; i <= K; i++) ib[b[i]] = i;
	for(int i = 1; i <= n; i++) if(ia[i] && ib[i]) {
		int v = ia[i] - ib[i];
		if(v <= 0) v += K;
		cnt[v]++;
	}
	for(int i = 1; i <= n; i++) mx = std::max(mx, cnt[i]);
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= K; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= K; i++) scanf("%d", &b[i]);
	solve();
	std::reverse(b + 1, b + K + 1);
	solve();
	int tot = 0;
	for(int i = 1; i <= n; i++) vis[a[i]] = vis[b[i]] = true;
	for(int i = 1; i <= n; i++) tot += vis[i];
	printf("%d\n", n - tot + mx);
	return 0;
}