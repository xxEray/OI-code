#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N];

int order[N];
std::set<int> st;

std::vector<std::array<int, 3>> vct[N];

struct SegmentTree {
	LL t[N << 2], lazy[N << 2];
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { t[x] += qv, lazy[x] += qv; return; }
		int mid = (l + r) >> 1;
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]) + lazy[x];
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid) + lazy[x];
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r) + lazy[x];
		else return std::max(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r)) + lazy[x];
	}
} seg;

int main() {
#ifndef DEBUG
	freopen("exchange.in", "r", stdin);
	freopen("exchange.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) order[i] = i;
	std::sort(order + 1, order + n + 1, [&](int x, int y) { return a[x] > a[y]; });
	for(int o = 1; o <= n; o++) {
		int i = order[o];
		std::vector<int> pre(m + 1), nxt;
		auto it = st.emplace(i).first;
		for(int j = 0; j <= m; j++) {
			pre[j] = *it;
			if(it == st.begin()) break;
			--it;
		}
		it = st.find(i);
		for(int j = 0; j <= m; j++) {
			nxt.emplace_back(*it);
			++it;
			if(it == st.end()) break;
		}
		for(int j = 0; j < (int)nxt.size(); j++) if(pre[m - j])
			vct[nxt[j]].push_back({!j || !pre[m - j + 1] ? 1 : pre[m - j + 1] + 1, pre[m - j], a[i]});
	}
	LL ans = -LLINF;
	for(int i = 1; i <= n; i++) {
		// printf("i = %d\n", i);
		for(auto [l, r, v] : vct[i]) seg.add(l, r, v); // , printf("[%d, %d] += %d\n", l, r, v);
		ans = std::max(ans, seg.query(1, i));
	}
	printf("%lld\n", ans);
	return 0;
}