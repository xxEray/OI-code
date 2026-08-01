#include <bits/stdc++.h>

const int N = 40 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int cnt[N];
int ans[N], acnt[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memset(ans, 0x3f, sizeof(ans));
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++) {
		for(int i = 1; i <= n; i++) cnt[i] = 0;
		int ret = 0;
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) {
			ret += std::accumulate(cnt + a[i] + 1, cnt + n + 1, 0);
			cnt[a[i]] = 1;
		}
		int k = __builtin_popcount(s);
		if(ret < ans[k]) ans[k] = ret, acnt[k] = 1;
		else if(ret == ans[k]) acnt[k]++;
	}
	for(int i = 1; i <= n; i++) printf("%d %d\n", ans[i], acnt[i]);
	return 0;
}