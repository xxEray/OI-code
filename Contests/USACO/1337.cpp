#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
struct Node { LL b, k, t; } a[N];

LL div_ceil(LL x, LL y) { if(y < 0) x = -x, y = -y; return x > 0 ? (x + y - 1) / y : x / y; }
LL div_floor(LL x, LL y) { if(y < 0) x = -x, y = -y; return x > 0 ? x / y : (x - y + 1) / y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].b);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].k);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].t);
		std::sort(a + 1, a + n + 1, [&](const Node &x, const Node &y) { return x.t < y.t; });
		bool flag = true;
		LL l = 0, r = LLONG_MAX;
		for(int i = 1; i <= n; i++) {
			if(a[i].t >= i) flag = false;
			int j = a[i].t;
			// h_j > h_i
			// k_j * t + b_j > k_i * t + b_i
			// (k_j - k_i) * t > (b_i - b_j)
			if(j) {
				if(a[j].k - a[i].k > 0) l = std::max(l, div_floor(a[i].b - a[j].b, a[j].k - a[i].k) + 1);
				else if(a[j].k - a[i].k < 0) r = std::min(r, div_ceil(a[i].b - a[j].b, a[j].k - a[i].k) - 1);
				else if(a[i].b - a[j].b >= 0) flag = false;
			}
			j++;
			// h_j <= h_i
			// k_j * t + b_j <= k_i * t + b_i
			// (k_j - k_i) * t <= (b_i - b_j)
			if(a[j].k - a[i].k > 0) r = std::min(r, div_floor(a[i].b - a[j].b, a[j].k - a[i].k));
			else if(a[j].k - a[i].k < 0) l = std::max(l, div_ceil(a[i].b - a[j].b, a[j].k - a[i].k));
			else if(a[i].b - a[j].b < 0) flag = false;
		}
		if(!flag || l > r) puts("-1");
		else printf("%lld\n", l);
	}
	return 0;
} /*
6
1
10
1
0
2
7 3
8 10
1 0
2
3 6
10 8
0 1
2
7 3
8 9
1 0
2
7 7
8 8
0 1
2
7 3
8 8
1 0
*/