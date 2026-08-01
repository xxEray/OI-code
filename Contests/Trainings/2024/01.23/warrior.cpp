#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL K;
int a[N];

std::vector<int> pos[N];

struct SegmentTree {
	int t1[N << 2], t2[N << 2], coe[N << 2], lzt[N << 2];
	bool lzcoe[N << 2];
	LL sum[N << 2];
	std::function<int(int, int)> calc1, calc2;
	void pushup(int x) {
		t1[x] = calc1(t1[x << 1], t1[x << 1 | 1]);
		t2[x] = calc2(t2[x << 1], t2[x << 1 | 1]);
		coe[x] = coe[x << 1] + coe[x << 1 | 1];
		sum[x] = sum[x << 1] + sum[x << 1 | 1];
	}
	void setcoe(int x) { coe[x] = 0, sum[x] = 0, lzcoe[x] = true; }
	void sett(int x, int v) { t1[x] = t2[x] = v, lzt[x] = v, sum[x] = (LL)v * coe[x]; }
	void lazydown(int x) {
		if(lzcoe[x]) setcoe(x << 1), setcoe(x << 1 | 1), lzcoe[x] = false;
		if(lzt[x] != -1) sett(x << 1, lzt[x]), sett(x << 1 | 1, lzt[x]), lzt[x] = -1;
	}
	void build(bool type, int x = 1, int l = 1, int r = n) {
		lzt[x] = -1, lzcoe[x] = false;
		if(l == r) { t1[x] = t2[x] = type ? l : n + 1, coe[x] = 1, sum[x] = t1[x]; return; }
		int mid = (l + r) >> 1;
		build(type, x << 1, l, mid), build(type, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	void makeempty(int ql, int qr, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("| makeempty %d %d\n", ql, qr);
		if(ql <= l && r <= qr) { setcoe(x); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) makeempty(ql, qr, x << 1, l, mid);
		if(qr > mid) makeempty(ql, qr, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	void modify(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("| modify %d %d %d\n", ql, qr, qv);
		if(calc2(t1[x], qv) == t1[x]) return;
		if(ql <= l && r <= qr && calc2(t2[x], qv) == qv) { sett(x, qv); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) modify(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) modify(ql, qr, qv, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	LL query(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// if(x == 1) printf("| query %d %d %d\n", ql, qr, qv);
		if(ql <= l && r <= qr && calc2(t1[x], qv) == t1[x]) return sum[x];
		if(ql <= l && r <= qr && calc2(t2[x], qv) == qv) return (LL)qv * coe[x];
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return query(ql, qr, qv, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, qv, x << 1 | 1, mid + 1, r);
		else return query(ql, qr, qv, x << 1, l, mid) + query(ql, qr, qv, x << 1 | 1, mid + 1, r);
	}
	int rmost(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) return t2[x] <= qv ? l : 0;
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return rmost(ql, qr, qv, x << 1, l, mid);
		int ret = 0;
		if(t1[x << 1 | 1] <= qv) ret = rmost(ql, qr, qv, x << 1 | 1, mid + 1, r);
		if(ret) return ret;
		return ql <= mid ? rmost(ql, qr, qv, x << 1, l, mid) : 0;
	}
	int lmost(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// printf("| | lmost %d %d %d %d %d\n", ql, qr, qv, l, r);
		if(l == r) return t2[x] >= qv ? l : 0;
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql > mid) return lmost(ql, qr, qv, x << 1 | 1, mid + 1, r);
		int ret = 0;
		if(t1[x << 1] >= qv) ret = lmost(ql, qr, qv, x << 1, l, mid);
		if(ret) return ret;
		return qr > mid ? lmost(ql, qr, qv, x << 1 | 1, mid + 1, r) : 0;
	}
} segl, segr;

void makeempty(int ql, int qr) { /* printf("makeempty [%d, %d]\n", ql, qr); */ if(ql <= qr) segl.makeempty(ql, qr), segr.makeempty(ql, qr); }
void modify(int ql, int qr, int qvl, int qvr) {
	if(ql > qr) return;
	int ll = segr.lmost(ql, qr, qvl + 1), rr = segl.rmost(ql, qr, qvr);
	// printf("modify [%d, %d] (%d, %d) (ll=%d, rr=%d)\n", ql, qr, qvl, qvr, ll, rr);
	if(ll && rr && ll <= rr) {
		segl.modify(ll, rr, qvl), segr.modify(ll, rr, qvr + 1);
		if(ql <= ll - 1) segr.modify(ql, ll - 1, qvl + 1), segl.modify(ql, ll - 1, qvl), segl.makeempty(ql, ll - 1), segr.makeempty(ql, ll - 1);
		if(rr + 1 <= qr) segl.modify(rr + 1, qr, qvr), segr.modify(rr + 1, qr, qvr + 1), segl.makeempty(rr + 1, qr), segr.makeempty(rr + 1, qr);
	} else segl.modify(ql, qr, qvl), segr.modify(ql, qr, qvl + 1), segl.makeempty(ql, qr), segr.makeempty(ql, qr);
}
LL query(int ql, int qr, int qvl, int qvr) {
	if(ql > qr) return 0;
	int ll = segr.lmost(ql, qr, qvl + 1), rr = segl.rmost(ql, qr, qvr);
	// printf("query [%d, %d] (%d, %d) = %lld (ll=%d, rr=%d)\n", ql, qr, qvl, qvr, !ll || !rr || ll > rr ? 0LL : segr.query(ll, rr, qvr + 1) - segl.query(ll, rr, qvl), ll, rr);
	return !ll || !rr || ll > rr ? 0LL : segr.query(ll, rr, qvr + 1) - segl.query(ll, rr, qvl);
}

int main() {
#ifndef DEBUG
	freopen("warrior.in", "r", stdin);
	freopen("warrior.out", "w", stdout);
#endif
	segl.calc1 = [&](int x, int y) { return x < y ? x : y; }, segr.calc1 = [&](int x, int y) { return x > y ? x : y; }, segl.calc2 = segr.calc1, segr.calc2 = segl.calc1;
	scanf("%d%lld", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]].emplace_back(i);
	segl.build(true), segr.build(false);
	std::vector<int> ans;
	for(int i = 1; i <= n; i++) if(!pos[i].empty()) {
		int sz = pos[i].size();
		auto count = [&](int x) -> LL {
			LL sum = 0;
			if(x) {
				for(int j = 0; j < sz - x + 1; j++) sum += query(j ? pos[i][j - 1] + 1 : 1, pos[i][j], pos[i][j + x - 1], n);
			} else {
				sum += query(1, n, 1, n);
			}
			// printf("count(%d) = %lld\n", x, sum);
			return sum;
		};
		int l = 0, r = sz + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(count(mid) >= K) l = mid + 1;
			else r = mid;
		}
		l--;
		K -= (l == sz ? 0 : count(l + 1));
		if(l) {
			for(int j = 0; j < sz - l + 1; j++) modify(j ? pos[i][j - 1] + 1 : 1, pos[i][j], pos[i][j + l - 1], j + l == sz ? n : pos[i][j + l] - 1);
			for(int j = sz - l + 1; j < sz; j++) makeempty(j ? pos[i][j - 1] + 1 : 1, pos[i][j]);
			makeempty(pos[i].back() + 1, n);
		} else {
			for(int j = 0; j < sz; j++) modify(j ? pos[i][j - 1] + 1 : 1, pos[i][j], j ? pos[i][j - 1] + 1 : 1, pos[i][j] - 1);
			modify(pos[i].back() + 1, n, pos[i].back() + 1, n);
			for(int j = 0; j < sz; j++) makeempty(pos[i][j], pos[i][j]);
		}
		// printf("append %d of %d (K = %lld)\n", l, i, K);
		while(l--) ans.emplace_back(i);
	}
	for(auto x : ans) printf("%d ", x);
	puts("");
	return 0;
} /*
3 3
3 2 1
*/