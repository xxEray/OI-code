#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m, Q;
int a[N];

int cnt[N];

int ans;
struct SegmentTree {
	int t[N << 2];
	std::vector<int> vct[N << 2];
	void build(int x = 1, int l = 1, int r = n) {
		t[x] = r - l + 1;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
	}
	void link(int ql, int qr, int qid, int x = 1, int l = 1, int r = n) {
		if(ql <= l && r <= qr) { vct[x].emplace_back(qid), cnt[qid]++; return; }
		int mid = (l + r) >> 1;
		if(ql <= mid) link(ql, qr, qid, x << 1, l, mid);
		if(qr > mid) link(ql, qr, qid, x << 1 | 1, mid + 1, r);
	}
	void modify(int qind, int x = 1, int l = 1, int r = n) {
		t[x]--;
		if(!t[x]) for(int i : vct[x]) if(!--cnt[i]) ans++;
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qind <= mid) modify(qind, x << 1, l, mid);
		else modify(qind, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	seg.build();
	for(int i = 1; i <= m; i++) { int l, r; scanf("%d%d", &l, &r); seg.link(l, r, i); }
	scanf("%d", &Q);
	while(Q--) {
		int x;
		scanf("%d", &x);
		x = (x + ans - 1) % n + 1;
		a[x]--;
		if(!a[x]) seg.modify(x);
		printf("%d\n", ans);
	}
	return 0;
}