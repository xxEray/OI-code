#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
int a[N];

std::set<int> occur[N];

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) occur[i].clear();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), occur[a[i]].emplace(i);
		int ans = 0, left = 0;
		for(int i = 1; i <= n; i++) if(occur[i].size() >= 2) bit.add(*++occur[i].rbegin() + 1, *occur[i].rbegin());
		for(int i = n, j = n; i >= 1; i--) {
			if(left > i) left = 0;
			auto it = occur[a[i]].find(i);
			if(it != occur[a[i]].begin()) bit.add(*--it + 1, i);
			while(j > left && bit.query(j)) j--;
			if(j > left) {
				occur[a[j]].erase(j);
				left = j;
				ans++;
			}
		}
	}
	return 0;
}