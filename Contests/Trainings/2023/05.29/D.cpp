#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;
struct Node { int l, r; LL w; } c[N];

LL a[N], b[N];
LL mx;
int L, R;

bool check(LL x) {
	for(int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];
	LL tot = mx - x;
	std::multiset<std::pair<int, LL>> st;
	bool flag = true;
	for(int i = 1, j = 1; i <= L; i++) {
		b[i] += b[i - 1];
		for(; j <= m && c[j].l == i; j++) if(c[j].r >= R) st.insert({c[j].r, c[j].w});
		LL need = std::max((b[i] + tot - x + 1) / 2, 0LL);
		if(need > tot) { flag = false; break; }
		while(!st.empty() && need) {
			auto p = *st.rbegin();
			st.erase(--st.end());
			LL now = std::min({need, p.second, tot});
			assert(now);
			need -= now, tot -= now, p.second -= now;
			b[i] -= now, b[p.first + 1] += 2 * now;
			if(p.second) st.insert({p.first, p.second});
		}
		if(need) { flag = false; break; }
		assert(b[i] + tot <= x);
	}
	for(int i = L + 1; i <= n; i++) b[i] += b[i - 1], flag &= (b[i] <= x);
	if(flag) return true;
	flag = true;
	st.clear();
	x--;
	tot = mx - x;
	for(int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];
	for(int i = 1, j = 1; i <= L; i++) {
		b[i] += b[i - 1];
		for(; j <= m && c[j].l == i; j++) if(c[j].r >= R) st.insert({c[j].r, c[j].w});
		LL need = std::max((b[i] + tot - (x + 1) + 1) / 2, 0LL);
		if(need > tot) { flag = false; break; }
		while(!st.empty() && need) {
			auto p = *st.rbegin();
			st.erase(--st.end());
			LL now = std::min({need, p.second, tot});
			assert(now);
			need -= now, tot -= now, p.second -= now;
			b[i] -= now, b[p.first + 1] += 2 * now;
			if(p.second) st.insert({p.first, p.second});
		}
		if(need) { flag = false; break; }
		assert(b[i] + tot <= x + 1);
	}
	for(int i = L + 1; i <= n; i++) b[i] += b[i - 1], flag &= (b[i] <= x + 1);
	return flag;
}

int main() {
#ifndef DEBUG
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%lld", &c[i].l, &c[i].r, &c[i].w);
		if(c[i].l > c[i].r) std::swap(c[i].l, c[i].r);
		c[i].r--, a[c[i].l] += c[i].w, a[c[i].r + 1] -= c[i].w;
	}
	std::sort(c + 1, c + m + 1, [&](Node x, Node y) { return x.l < y.l; });
	for(int i = 1; i <= n; i++) a[i] += a[i - 1];
	mx = *std::max_element(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) if(a[i] == mx) { L = i; break; }
	for(int i = n; i >= 1; i--) if(a[i] == mx) { R = i; break; }
	assert(L && R);
	// printf("L = %d, R = %d\n", L, R);
	LL l = 0, r = mx;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
} /*
20 20
4 19 1
9 8 1
3 18 1
11 7 1
18 14 1
18 5 1
15 5 1
5 11 1
1 13 1
3 19 1
15 18 1
7 17 1
20 6 1
11 20 1
16 1 1
19 16 1
19 11 1
*/