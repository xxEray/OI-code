#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N];

struct BIT {
	int t[N << 2];
	void clear() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit;

std::set<int> st;

int tmp[N];
int val[N];
void discrete() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	int c = n;
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) {
		int v = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
		val[v] = a[i], a[i] = v;
	}
}

std::vector<std::pair<int, int>> vct;

int main() {
#ifdef DEBUG
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		vct.clear();
		st.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++){ int b; scanf("%1d", &b); if(b) st.emplace(i); }
		discrete();
		bit.clear();
		for(int i = 1; i <= n; i++) {
			vct.emplace_back(val[a[i]], (i - 1) - bit.query(a[i]));
			bit.add(a[i], 1);
		}
		std::sort(vct.begin(), vct.end());
		bit.clear();
		long long ans = 0;
		for(auto [x, v] : vct) {
			int l = 1, r = n + 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(mid - 1 - bit.query(mid - 1) <= v) l = mid + 1;
				else r = mid;
			}
			int pos = l - 1;
			auto it = st.upper_bound(pos);
			if(it == st.begin()) bit.add(pos, 1);
			else {
				pos = *--it;
				bit.add(pos, 1);
				ans += x;
				st.erase(pos);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
8
553392581 207639481 491561613 443879346 304842092 480359898 422896902 863493067
10000001
*/