#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, K;
int a[N];

int mn[N], mx[N], cnt[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= K; i++) cnt[i] = 0, mn[i] = n + 1, mx[i] = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			cnt[a[i]]++;
			mn[a[i]] = std::min(mn[a[i]], i);
			mx[a[i]] = std::max(mx[a[i]], i);
		}
		for(int i = K - 1; i >= 1; i--) mn[i] = std::min(mn[i], mn[i + 1]), mx[i] = std::max(mx[i], mx[i + 1]);
		// for(int i = 1; i <= K; i++) printf("%d: mn = %d, mx = %d\n", i, mn[i], mx[i]);
		for(int i = 1; i <= K; i++) printf("%d ", 2 * (!cnt[i] ? 0 : mx[i] - mn[i] + 1));
		puts("");
	}
	return 0;
}