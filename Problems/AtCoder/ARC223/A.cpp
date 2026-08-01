#include <bits/stdc++.h>

typedef long long LL;

const int N = 60 + 5;

int n;
LL w[N], v[N];

LL prew[N], prev[N];

LL calc(int i, LL W) {
	if(i == 0) return 0;
	if(W < w[i]) return calc(i - 1, W);
	else return std::max(prev[i - 1], calc(i - 1, W - w[i]) + v[i]);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL W;
		scanf("%d%lld", &n, &W);
		for(int i = 1; i <= n; i++) {
			scanf("%lld%lld", &w[i], &v[i]);
			prew[i] = prew[i - 1] + w[i], prev[i] = prev[i - 1] + v[i];
		}
		printf("%lld\n", calc(n, W));
	}
	return 0;
}