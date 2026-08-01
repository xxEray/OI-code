#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

typedef long long LL;

int a[N], b[N];
int n, m;

struct SegTree {
	LL t[N << 2], ladd[N << 2];
	inline void lazy_down(int x) {
		t[x << 1] += ladd[x];
		t[x << 1 | 1] += ladd[x];
		ladd[x << 1] += ladd[x];
		ladd[x << 1 | 1] += ladd[x];
		ladd[x] = 0;
	}
	void set_add(int ql, int qr, LL qadd, int x = 1, int l = 1, int r = m) {
		if(ql <= l && r <= qr) { t[x] += qadd, ladd[x] += qadd; return; }
		int mid = l + ((r - l) >> 1);
		lazy_down(x);
		if(ql <= mid) set_add(ql, qr, qadd, x << 1, l, mid);
		if(qr > mid) set_add(ql, qr, qadd, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	LL query_min(int ql, int qr, int x = 1, int l = 1, int r = m) {
		if(ql <= l && r <= qr) return t[x];
		int mid = l + ((r - l) >> 1);
		lazy_down(x);
		if(qr <= mid) return query_min(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query_min(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query_min(ql, qr, x << 1, l, mid), query_min(ql, qr, x << 1 | 1, mid + 1, r));
	}
};

SegTree ans1; // ans[][i]
SegTree ans2; // ans[][i] + m - i

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%d%d", &a[i], &b[i]);
	for(int i = 1; i <= m; i++) ans2.set_add(i, i, m - i);
	for(int i = 1; i <= n; i++) {
		LL tmp = ans2.query_min(1, b[i] + 1) - ((LL)m - b[i] - 1);
		ans1.set_add(b[i] + 1, b[i] + 1, std::min(tmp - ans1.query_min(b[i] + 1, b[i] + 1), 0LL));
		ans2.set_add(b[i] + 1, b[i] + 1, std::min(tmp + m - (b[i] + 1) - ans2.query_min(b[i] + 1, b[i] + 1), 0LL));
		ans1.set_add(a[i], b[i], INF);
		ans2.set_add(a[i], b[i], INF);
		ans1.set_add(1, m, 1);
		ans2.set_add(1, m, 1);
		tmp = ans1.query_min(1, m);
		// for(int j = 1; j <= m; j++) std::printf("%lld ", ans1.query_min(j, j));
		// std::printf("\n");
		if(tmp >= INF) std::printf("-1\n");
		else std::printf("%lld\n", tmp);
	}
	return 0;
}