#include <bits/stdc++.h>

const int N = 50 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;
int a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		long long sum = 0;
		int mna = INF, mxa = -INF, mxb = -INF, mnb = INF;
		for(int i = 1; i <= n; i++) sum += a[i], mna = std::min(mna, a[i]), mxa = std::max(mxa, a[i]);
		for(int i = 1; i <= m; i++) mxb = std::max(mxb, b[i]), mnb = std::min(mnb, b[i]);
		printf("%lld\n", ((K & 1) ? std::max(sum, sum - mna + mxb) : std::min(sum, sum - mxa + mnb)));
	}
	return 0;
}