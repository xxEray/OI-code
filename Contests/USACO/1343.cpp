#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, Q;
LL a[N];
struct Query { LL a, b; int id; } q[N];

std::vector<std::pair<LL, LL>> vct;
LL out[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) scanf("%lld%lld", &q[i].a, &q[i].b), q[i].id = i;
	std::sort(q + 1, q + Q + 1, [&](const Query &x, const Query &y) { return x.b * y.a < y.b * x.a; });
	LL sum1 = 0, sum2 = 0;
	for(int i = 1; i <= n; i++) sum2 += a[i];
	for(int i = 1; i <= n; i++) {
		sum2 -= a[i];
		vct.emplace_back((i - 1) * a[i] - sum1, sum2 - (n - i) * a[i]);
		sum1 += a[i];
	}
	int p = 0;
	for(int i = 1; i <= Q; i++) {
		while(p + 1 < n && vct[p].first * q[i].a + vct[p].second * q[i].b >= vct[p + 1].first * q[i].a + vct[p + 1].second * q[i].b) p++;
		out[q[i].id] = vct[p].first * q[i].a + vct[p].second * q[i].b;
	}
	for(int i = 1; i <= Q; i++) printf("%lld\n", out[i]);
	return 0;
}