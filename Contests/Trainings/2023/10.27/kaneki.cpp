#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n, Q;
int a[N];

struct SegmentTree {
	bool leaf[N << 2];
	LL sum[N << 2], fsum[N << 2], lzmul[N << 2], lzadd[N << 2];
	int cnt[N << 2], frozen[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		fsum[x] = 0, lzmul[x] = 1, lzadd[x] = 0, frozen[x] = 0;
		if(l == r) { sum[x] = a[l], cnt[x] = 1, leaf[x] = true; return; }
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % MOD;
		cnt[x] = cnt[x << 1] + cnt[x << 1 | 1];
		assert(cnt[x] == r - l + 1);
	}
	void pushadd(int x, LL qv) {
		if(!frozen[x]) (sum[x] += cnt[x] * qv) %= MOD, (lzadd[x] += qv) %= MOD;
	}
	void pushmul(int x, LL qv) {
		if(!frozen[x]) (sum[x] *= qv) %= MOD, (lzmul[x] *= qv) %= MOD, (lzadd[x] *= qv) %= MOD;
	}
	void pushdown(int x) {
		pushmul(x << 1, lzmul[x]), pushmul(x << 1 | 1, lzmul[x]);
		pushadd(x << 1, lzadd[x]), pushadd(x << 1 | 1, lzadd[x]);
		lzadd[x] = 0, lzmul[x] = 1;
	}
	void pushup(int x) {
		if(leaf[x]) {
			assert(!sum[x] || !fsum[x]);
			int v = sum[x] + fsum[x];
			sum[x] = !frozen[x] * v;
			fsum[x] = (bool)frozen[x] * v;
			cnt[x] = !frozen[x];
		} else {
			sum[x] = !frozen[x] * (sum[x << 1] + sum[x << 1 | 1]) % MOD;
			fsum[x] = (fsum[x << 1] + fsum[x << 1 | 1] + (frozen[x] ? sum[x << 1] + sum[x << 1 | 1] : 0)) % MOD;
			cnt[x] = !frozen[x] * (cnt[x << 1] + cnt[x << 1 | 1]);
		}
	}
	void addfreeze(int ql, int qr, int qv, int x = 1, int l = 1, int r = n) {
		// printf("addfreeze %d %d %d %d %d %d\n", ql, qr, qv, x, l, r);
		if(ql <= l && r <= qr) { if(!leaf[x]) pushdown(x); frozen[x] += qv; pushup(x); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) addfreeze(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) addfreeze(ql, qr, qv, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	void add(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(frozen[x]) return;
		if(ql <= l && r <= qr) { pushadd(x, qv); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) add(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) add(ql, qr, qv, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	void multiply(int ql, int qr, LL qv, int x = 1, int l = 1, int r = n) {
		if(frozen[x]) return;
		if(ql <= l && r <= qr) { pushmul(x, qv); return; }
		int mid = (l + r) >> 1;
		pushdown(x);
		if(ql <= mid) multiply(ql, qr, qv, x << 1, l, mid);
		if(qr > mid) multiply(ql, qr, qv, x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	LL query(int ql, int qr, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) return (sum[x] + fsum[x]) % MOD;
		int mid = (l + r) >> 1;
		pushdown(x);
		if(qr <= mid) return query(ql, qr, x << 1, l, mid);
		else if(ql > mid) return query(ql, qr, x << 1 | 1, mid + 1, r);
		else return (query(ql, qr, x << 1, l, mid) + query(ql, qr, x << 1 | 1, mid + 1, r)) % MOD;
	}
} seg;

std::vector<std::pair<int, int>> melt[N];

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	seg.build();
	for(int q = 1; q <= Q; q++) {
		int type, l, r, x;
		scanf("%d", &type);
		if(type == 1) scanf("%d%d%d", &l, &r, &x), seg.add(l, r, x);
		else if(type == 2) scanf("%d%d%d", &l, &r, &x), seg.multiply(l, r, x);
		else if(type == 3) scanf("%d%d%d", &l, &r, &x), seg.addfreeze(l, r, 1), melt[q + x].push_back({l, r});
		else scanf("%d%d", &l, &r), printf("%lld\n", seg.query(l, r));
		for(const auto &p : melt[q]) seg.addfreeze(p.first, p.second, -1);
	}
	return 0;
} /*
10 6
655055752 958611006 12090236 735012055 192837391 331630454 346553801 180077963 911260505 45661659 
3 6 7 6
3 4 6 2
3 7 10 1
2 1 4 601961745
2 4 8 936715446
4 5 6

10 12
4 2 1 5 10 3 2 4 6 7
2 3 7 4
1 2 9 5
3 2 4 5
3 4 7 2
4 3 9
1 1 8 2
2 4 5 2
3 6 8 2
4 2 3
1 2 10 6
2 7 9 3
4 1 10

*/