#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;

struct SegmentTree {
	int cnt[N << 2], sum[N << 2], del[N << 2];
	void get(int to, int v, int x, int l, int r) {
		if(l == r) {
			if(!v) cnt[to] += cnt[x], sum[to] += sum[x];
			return;
		}
		int mid = (l + r) >> 1;
		if(cnt[x << 1 | 1] <= v) get(to, v - cnt[x << 1 | 1] + del[x << 1 | 1], x << 1, l, mid);
		else {
			cnt[to] += cnt[x] - cnt[x << 1 | 1], sum[to] += sum[x] - sum[x << 1 | 1];
			get(to, v, x << 1 | 1, mid + 1, r);
		}
	}
	void modify(int qind, int qk, int qv, int x = 1, int l = 1, int r = n) {
		if(l == r) {
			if(qk == 0) cnt[x] = 1, sum[x] = qv, del[x] = 0;
			else cnt[x] = sum[x] = 0, del[x] = qv;
			return;
		}
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, qk, qv, x << 1, l, mid);
		else modify(qind, qk, qv, x << 1 | 1, mid + 1, r);
		if(del[x << 1 | 1]) {
			cnt[x] = cnt[x << 1 | 1], sum[x] = sum[x << 1 | 1];
			if(del[x << 1 | 1] <= cnt[x << 1]) del[x] = 0, get(x, del[x << 1 | 1], x << 1, l, mid);
			else del[x] = del[x << 1 | 1] - cnt[x << 1];
			del[x] += del[x << 1];
		} else {
			cnt[x] = cnt[x << 1] + cnt[x << 1 | 1];
			sum[x] = sum[x << 1] + sum[x << 1 | 1];
			del[x] = del[x << 1];
		}
	}
	int query() { return sum[1]; }
} seg;

int main() {
#ifndef DEBUG
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) { int k, v; scanf("%d%d", &k, &v); seg.modify(i, k, v); }
	while(m--) {
		int p, k, v;
		scanf("%d%d%d", &p, &k, &v);
		seg.modify(p, k, v);
		printf("%d\n", seg.query());
	}
	return 0;
}