#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;

int n;
LL E;
LL a[N], b[N];

bool check(int l, int r) {
	LL sum = 0;
	for(int i = l; i <= r; i++) sum += -a[i] + b[i];
	if(sum < 0) return false;
	for(int i = l; i <= r; i++) {
		sum = 0;
		for(int j = l; j <= r; j++) if(j != i) sum += std::min(-a[j] + b[j], 0LL);
		if(E + sum < a[i]) return false;
	}
	return true;
}

int main() {
	scanf("%d%lld", &n, &E);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) for(int j = i; j <= n; j++) ans += check(i, j);
	printf("%lld\n", ans);
	return 0;
}