#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;

LL m; int K;
LL pre[21][N];

int main() {
	for(int k = 2; k <= 20; k++) for(int i = 1; i <= 2000000; i++) pre[k][i] = pre[k][i - 1] + (__builtin_popcount(i) == k);
	// for(int k = 2; k <= 20; k++) printf("%lld ", pre[k][2000000] - pre[k][1000000]);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%d", &m, &K);
		int mn = 1000000, cnt = 0;
		for(int i = 1; i <= 1000000; i++) if(pre[K][i << 1] - pre[K][i] == m) mn = std::min(mn, i), cnt++;
		printf("%d %d\n", mn, cnt);
	}
	return 0;
}