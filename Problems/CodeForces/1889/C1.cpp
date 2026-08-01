#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m, K;

struct Node { int l, r; } a[N];

struct BIT {
	int t[N];
	void init() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	void add(int l, int r, int v) { add(l, v), r < n ? add(r + 1, -v) : (void)0;}
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

std::vector<int> pos;
std::map<std::pair<int, int>, int> mp;
int val[N][2];
int cnt[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mp.clear();
		scanf("%d%d%d", &n, &m, &K);
		bit.init();
		for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].l, &a[i].r), bit.add(a[i].l, a[i].r, 1);
		pos.clear();
		for(int i = 1; i <= n; i++) val[i][0] = val[i][1] = 0;
		for(int i = 1; i <= m; i++) cnt[i] = 0;
		for(int i = 1; i <= n; i++) if(bit.query(i) <= 2) pos.push_back(i);
		for(int i = 1; i <= m; i++) {
			for(auto it = std::lower_bound(pos.begin(), pos.end(), a[i].l); it != pos.end() && *it <= a[i].r; it++)
				val[*it][val[*it][0] ? 1 : 0] = i;
		}
		// puts("val:");
		// for(int i = 1; i <= n; i++) printf("%d %d\n", val[i][0], val[i][1]);
		int ret = 0;
		for(int i = 1; i <= n; i++)
			if(!val[i][0]) ret += (bit.query(i) == 0);
			else if(val[i][0] && !val[i][1]) cnt[val[i][0]]++;
			else mp[{val[i][0], val[i][1]}]++;
		int mx = 0, scmx = 0;
		for(int i = 1; i <= m; i++)
			if(cnt[i] > mx) scmx = mx, mx = cnt[i];
			else if(cnt[i] > scmx) scmx = cnt[i];
		int ans = mx + scmx + ret;
		for(int i = 1; i <= n; i++) if(val[i][1])
			ans = std::max(ans, ret + cnt[val[i][0]] + cnt[val[i][1]] + mp[{val[i][0], val[i][1]}]);
		printf("%d\n", ans);
	}
	return 0;
} /*
6
2 3 2
1 2
1 2
1 1
5 3 2
1 3
2 4
3 5
10 6 2
1 5
6 10
2 2
3 7
5 8
1 4
100 6 2
1 100
1 100
1 100
1 100
1 100
1 100
1000 2 2
1 1
1 1
20 5 2
9 20
3 3
10 11
11 13
6 18

*/