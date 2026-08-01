#include <bits/stdc++.h>
inline char rdc() {
	const int D = 1 << 23;
	static char buf[D], *p1, *p2;
	static std::streambuf *in = std::cin.rdbuf();
	return (p1 == p2 && (p2 = (p1 = buf) + in->sgetn(buf, D), p1 == p2) ? -1 : *p1++);
}
template<typename T> void read(T &x) {
	char c = rdc(), fl = 0;
	while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
	for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
    if(fl) x = -x;
}
inline void wrtc(char c) {
	static std::streambuf *out = std::cout.rdbuf();
	out->sputc(c);
}
template<typename T> void write(T x, char ch = 0) {
	static char c[60]; int top = 0;
    if(x < 0) wrtc('-'), x = -x;
	do c[++top] = x % 10, x /= 10; while(x);
	while(top) wrtc(c[top--] + '0');
	if(ch) wrtc(ch);
}

#undef assert
void assert(...) {}

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
const int BD = 1e5;

int n;
struct Segment { int l, r; } a[N];

int lim[N];

std::vector<Segment> ans;

struct SegmentTree1 {
	int t[N << 2], tid[N << 2], lazy[N << 2];
	void set_lazy(int x, int v) { t[x] += v, lazy[x] += v; }
	void lazy_down(int x) { set_lazy(x << 1, lazy[x]), set_lazy(x << 1 | 1, lazy[x]), lazy[x] = 0; }
	void build(int x = 1, int l = 1, int r = n) {
		lazy[x] = 0;
		if(l == r) { t[x] = 0, tid[x] = l; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = 0, tid[x] = l;
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { set_lazy(x, qv); return; }
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::max(t[x << 1], t[x << 1 | 1]);
		tid[x] = (t[x] == t[x << 1] ? tid[x << 1] : tid[x << 1 | 1]);
	}
	std::pair<int, int> query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return {t[x], tid[x]};
		int mid = (l + r) >> 1;
		lazy_down(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else {
			auto p1 = query(ql, qr, x << 1, l, mid), p2 = query(ql, qr, x << 1 | 1, mid + 1, r);
			return p1.first >= 0 ? p1 : p2;
		}
	}
} seg1;

struct SegmentTree2 {
	std::pair<int, int> t[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = {INF, 0}; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		t[x] = {INF, 0};
	}
	void modify(int qind, const std::pair<int, int> &qv, int x = 1, int l = 1, int r = n) {
		if(l == r) { t[x] = qv; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qv, x << 1, l, mid);
		else modify(qind, qv, x << 1 | 1, mid + 1, r);
		t[x] = std::min(t[x << 1], t[x << 1 | 1]);
	}
	std::pair<int, int> query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return t[x];
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return std::min(query(ql, qr, x << 1, l, mid), query(ql, qr, x << 1 | 1, mid + 1, r));
	}
} seg2;

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq[N];
std::set<std::pair<int, int>> st;

inline void assign1(int i, int v) {
	assert(lim[i] != n);
	seg1.modify(v, lim[i] - 1, 1);
	assert(pq[lim[i]].top() == std::make_pair(a[i].r, i));
	pq[lim[i]].pop();
	seg2.modify(lim[i], pq[lim[i]].empty() ? std::make_pair(INF, 0) : pq[lim[i]].top());
	lim[i] = v;
	pq[lim[i]].push({a[i].r, i});
	seg2.modify(lim[i], pq[lim[i]].empty() ? std::make_pair(INF, 0) : pq[lim[i]].top());
}
inline void assign2(int i, int v) {
	assert(lim[i] == n);
	seg1.modify(v, lim[i] - 1, 1);
	st.erase({a[i].r, i});
	seg2.modify(lim[i], st.empty() ? std::make_pair(INF, 0) : *st.begin());
	lim[i] = v;
	pq[lim[i]].push({a[i].r, i});
	seg2.modify(lim[i], pq[lim[i]].empty() ? std::make_pair(INF, 0) : pq[lim[i]].top());
}

bool check(int K, bool answer) {
	seg1.build(), seg2.build();
	for(int i = 1; i < n; i++) while(!pq[i].empty()) pq[i].pop();
	st.clear();
	for(int i = 1; i <= n; i++) lim[i] = n, i < n ? seg1.modify(i, i, -i) : (void)0, st.insert({a[i].r, i});
	for(int i = 1; i < n; i++) seg2.modify(i, pq[i].empty() ? std::make_pair(INF, 0) : pq[i].top());
	seg2.modify(n, st.empty() ? std::make_pair(INF, 0) : *st.begin());
	int p = 1;
	for(int i = 1; i <= n; i++) {
		int q = seg1.query(i, n).second;
		if(q < i) return false;
		int j = seg2.query(i, q).second;
		if(answer) ans.push_back({a[j].l, a[j].r});
		if(lim[j] < i) return false;
		if(lim[j] > i) lim[j] == n ? assign2(j, i) : assign1(j, i);
		for(; p <= n && a[p].l <= a[j].r; p++) if(lim[p] > lim[j] + K) assert(lim[p] == n), assign2(p, std::min(n, lim[j] + K));
	}
	return true;
}

int main() {
	int T; read(T);
	while(T--) {
		read(n);
		for(int i = 1; i <= n; i++) read(a[i].l), read(a[i].r);
		std::sort(a + 1, a + n + 1, [&](const Segment &x, const Segment &y) { return x.l < y.l; });
		int l = 0, r = n;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid, false)) r = mid;
			else l = mid + 1;
		}
		ans.clear(), check(l, true);
		write(l, '\n');
		for(auto &p : ans) write(p.l, ' '), write(p.r, '\n');
	}
	return 0;
}