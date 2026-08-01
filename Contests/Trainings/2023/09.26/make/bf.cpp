#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m, Q;
struct Node { int l, r; } a[N];

LL last[N];

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].l, &a[i].r);
	while(Q--) {
		LL x;
		scanf("%lld", &x);
		for(int i = 1; i <= n; i++) last[i] = -1;
		LL ans = 0;
		LL cnt = 0;
		auto perform = [&](int i) -> void {
			cnt++;
			if(last[i] != -1 && cnt - last[i] - 1 >= x) ans++;
			last[i] = cnt;
		};
		for(int i = 1; i <= m; i++)
			for(int j = a[i].l; j <= a[i].r; j++)
				perform(j);
		printf("%lld ", ans);
	}
	puts("");
	return 0;
}