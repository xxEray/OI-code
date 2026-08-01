#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, Q;
int a[N];
struct Query { int p, v; } qr[N];

namespace Solve_v10 {
	LL ans;
	struct Solver {
		std::set<int> st;
		void init() {
			st.emplace(0), st.emplace(n + 1);
		}
		void insert(int x) {
			st.emplace(x);
			auto it = st.find(x);
			int lv = *std::prev(it), rv = *std::next(it);
			ans += (LL)(rv - x) * (x - lv);
		}
		void erase(int x) {
			auto it = st.find(x);
			int lv = *std::prev(it), rv = *std::next(it);
			ans -= (LL)(rv - x) * (x - lv);
			st.erase(x);
		}
	} solver[11];
	void main() {
		for(int j = 1; j <= 10; j++) solver[j].init();
		for(int i = 1; i <= n; i++) for(int j = a[i]; j <= 10; j++) solver[j].insert(i);
		// printf("ans = %lld\n", ans);
		for(int q = 1; q <= Q; q++) {
			int p = qr[q].p, v = qr[q].v;
			if(a[p] < v) {
				for(int j = a[p]; j < v; j++) solver[j].erase(p);
			} else {
				for(int j = v; j < a[p]; j++) solver[j].insert(p);
			}
			a[p] = v;
			printf("%lld\n", 11LL * n * (n + 1) / 2 - ans);
		}
	}
}

namespace Solve_luangao {
	struct SegmentTree {
		int t[N << 2];
		void modify(int qind, int qv, int x = 1, int l = 1, int r = n) {
			if(l == r) { t[x] = qv; return; }
			int mid = (l + r) >> 1;
			if(qind <= mid) modify(qind, qv, x << 1, l, mid);
			else modify(qind, qv, x << 1 | 1, mid + 1, r);
			t[x] = std::min(t[x << 1], t[x << 1 | 1]);
		}
		int queryl(int qind, int qv, int x = 1, int l = 1, int r = n) {
			if(qind == 0) return 0;
			if(l == r) return (t[x] <= qv ? l : 0);
			int mid = (l + r) >> 1;
			if(qind <= mid) return queryl(qind, qv, x << 1, l, mid);
			else {
				int ret = 0;
				if(t[x << 1 | 1] <= qv) ret = queryl(qind, qv, x << 1 | 1, mid + 1, r);
				if(ret) return ret;
				return queryl(qind, qv, x << 1, l, mid);
			}
		}
		int queryr(int qind, int qv, int x = 1, int l = 1, int r = n) {
			if(qind == n + 1) return n + 1;
			if(l == r) return (t[x] <= qv ? l : n + 1);
			int mid = (l + r) >> 1;
			if(qind > mid) return queryr(qind, qv, x << 1 | 1, mid + 1, r);
			else {
				int ret = n + 1;
				if(t[x << 1] <= qv) ret = queryr(qind, qv, x << 1, l, mid);
				if(ret != n + 1) return ret;
				return queryr(qind, qv, x << 1 | 1, mid + 1, r);
			}
		}
	} seg;
	int lb[N], rb[N];
	void main() {
		for(int i = 1; i <= n; i++) seg.modify(i, a[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) {
			lb[i] = seg.queryl(i - 1, a[i]) + 1;
			rb[i] = seg.queryr(i + 1, a[i] - 1) - 1;
			ans += (LL)a[i] * (rb[i] - i + 1) * (i - lb[i] + 1);
			// printf("%d: lb=%d, rb=%d\n", i, lb[i], rb[i]);
		}
		// printf("ans = %lld\n", ans);
		for(int q = 1; q <= Q; q++) {
			int p = qr[q].p, v = qr[q].v;
			int lastv = a[p];
			std::vector<int> vct = {p};
			for(int i = seg.queryl(p - 1, a[p]); i >= 1; i = seg.queryl(i - 1, a[i])) vct.emplace_back(i);
			for(int i = seg.queryr(p + 1, a[p] - 1); i <= n; i = seg.queryr(i + 1, a[i] - 1)) vct.emplace_back(i);
			a[p] = v, seg.modify(p, v);
			for(int i = seg.queryl(p - 1, a[p]); i >= 1; i = seg.queryl(i - 1, a[i])) vct.emplace_back(i);
			for(int i = seg.queryr(p + 1, a[p] - 1); i <= n; i = seg.queryr(i + 1, a[i] - 1)) vct.emplace_back(i);
			std::sort(vct.begin(), vct.end()), vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
			// printf("vct: "); for(int x : vct) printf("%d ", x); puts("");
			for(int i : vct) {
				ans -= (LL)(i == p ? lastv : a[i]) * (rb[i] - i + 1) * (i - lb[i] + 1);
				lb[i] = seg.queryl(i - 1, a[i]) + 1;
				rb[i] = seg.queryr(i + 1, a[i] - 1) - 1;
				ans += (LL)a[i] * (rb[i] - i + 1) * (i - lb[i] + 1);
			}
			printf("%lld\n", ans);
		}
	}
}

int main() {
	scanf("%d%d", &n, &Q);
	int mx = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), mx = std::max(mx, a[i]);
	for(int i = 1; i <= Q; i++) scanf("%d%d", &qr[i].p, &qr[i].v), mx = std::max(mx, qr[i].v);
	if(mx <= 10) Solve_v10::main();
	else Solve_luangao::main();
	return 0;
}