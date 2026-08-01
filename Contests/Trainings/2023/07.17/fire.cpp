#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];
struct Query { int p, t, id; } qr[N << 1];
std::vector<std::pair<int, int>> vct[N << 1];

int vl[N], vr[N];

struct BIT {
	LL t[5 * N + 10];
	void add(int x, LL v) { /* printf("add %d\n", x);  */x += 3 * n + 5; while(x <= 5 * n + 9) t[x] += v, x += x & -x; }
	void add(int l, int r, LL v) { add(l, v), add(r + 1, -v); }
	LL query(int x) { /* printf("query %d\n", x);  */x += 3 * n + 5; LL ret = 0; while(x) ret += t[x], x -= x & -x; return ret; }
} bitv1, bitv2, bitvx, bitvxy;

LL out[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::vector<int> q;
	for(int i = 1; i <= n; i++) {
		while(!q.empty() && a[q.back()] < a[i]) q.pop_back();
		vl[i] = (q.empty() ? -n : q.back()) + 1;
		q.push_back(i);
	}
	q.clear();
	for(int i = n; i >= 1; i--) {
		while(!q.empty() && a[q.back()] <= a[i]) q.pop_back();
		vr[i] = (q.empty() ? n + 1 : q.back()) - 1;
		q.push_back(i);
	}
	// printf("vl: "); for(int i = 1; i <= n; i++) printf("%d ", vl[i]); puts("");
	// printf("vr: "); for(int i = 1; i <= n; i++) printf("%d ", vr[i]); puts("");
	for(int i = 1; i <= n; i++) {
		vct[vr[i] - vl[i] + 1].push_back({vr[i], a[i]});
		if(i - vl[i] >= 1) vct[i - vl[i]].push_back({i - 1, -a[i]});
		if(vr[i] - i >= 1) vct[vr[i] - i].push_back({vr[i], -a[i]});
	}
	for(int i = 1; i <= m; i++) {
		int t, l, r;
		scanf("%d%d%d", &t, &l, &r);
		t++;
		qr[2 * i - 1] = {l - 1, t, -i};
		qr[2 * i] = {r, t, i};
	}
	std::sort(qr + 1, qr + 2 * m + 1, [&](Query x, Query y) { return x.t > y.t; });
	for(int i = 2 * n, j = 1; i >= 1; i--) {
		for(auto &p : vct[i]) {
			int v = p.second, x = p.first, y = i;
			// printf("add triangle (%d, %d) %d\n", x, y, v);
			bitv1.add(-3 * n - 4, x, v), bitvx.add(x + 1, 2 * n, (LL)v * x);
			bitv2.add(-3 * n - 4, x - y - 1, v), bitvxy.add(x - y, 2 * n, (LL)v * (x - y - 1));
		}
		while(j <= 2 * m && qr[j].t == i) {
			int p = qr[j].p, t = qr[j].t;
			out[std::abs(qr[j].id)] += (qr[j].id > 0 ? 1 : -1) * (bitvx.query(p) + bitv1.query(p) * p - bitv2.query(p - t) * (p - t) - bitvxy.query(p - t));
			// printf("out[%d] = %lld (p=%d, t=%d)\n", std::abs(qr[j].id), out[std::abs(qr[j].id)], p, t);
			j++;
		}
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", out[i]);
	return 0;
} /*
5 5
9 3 2 6 5
1 1 3
2 1 5
3 2 5
4 3 3
5 3 5
*/