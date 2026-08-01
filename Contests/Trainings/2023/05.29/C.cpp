#include <bits/stdc++.h>

const int N = 5e5 + 5;

int n, Q;
int a[N];
std::vector<int> b[N];

int t[N];

int l[N], r[N];
std::set<int> rmn[N], lmx[N];
int lb[N], rb[N];

std::set<int> st;
std::vector<int> cancell[N], cancelr[N];

int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i < n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		int k, x;
		scanf("%d", &k);
		while(k--) scanf("%d", &x), b[i].push_back(x);
	}
	for(int i = 1; i <= n; i++) t[i] = 0;
	for(int i = 1; i < n; i++) {
		for(int x : b[i]) t[x] = i;
		l[i] = t[a[i]];
	}
	for(int i = 1; i <= n; i++) t[i] = n + 1;
	for(int i = n; i >= 1; i--) {
		r[i] = t[a[i]];
		for(int x : b[i]) t[x] = i;
	}
	l[0] = 0, r[0] = n + 1;
	l[n] = 0, r[n] = n + 1;
	// for(int i = 0; i <= n; i++) printf("%d: l=%d, r=%d\n", i, l[i], r[i]);
	for(int i = 0; i <= n; i++) cancell[l[i]].push_back(i), cancelr[r[i]].push_back(i);
	for(int i = 1; i <= n; i++) rmn[i].insert(n), lmx[i].insert(1);
	for(int i = 0; i <= n; i++) {
		for(int x : cancelr[i]) st.erase(x);
		auto it = st.lower_bound(l[i]);
		if(it != st.end()) rmn[*it + 1].insert(i); // , printf("rbound [%d .. %d] -> %d\n", *it + 1, i, i);
		st.insert(i);
	}
	st.clear();
	for(int i = n; i >= 0; i--) {
		auto it = st.lower_bound(r[i]);
		if(it != st.begin()) it--, lmx[*it].insert(i + 1); // , printf("lbound [%d .. %d] -> %d\n", i + 1, *it, i + 1);
		st.insert(i);
		for(int x : cancell[i]) st.erase(x);
	}
	std::set<int> st2;
	for(int i = 1; i <= n; i++) {
		for(int x : rmn[i]) st2.insert(x);
		while(*st2.begin() < i) st2.erase(st2.begin());
		rb[i] = *st2.begin();
	}
	st2.clear();
	for(int i = n; i >= 1; i--) {
		for(int x : lmx[i]) st2.insert(x);
		while(*st2.rbegin() > i) st2.erase(--st2.end());
		lb[i] = *st2.rbegin();
	}
	// for(int i = 1; i <= n; i++) printf("ans[%d]: [%d .. %d]\n", i, lb[i], rb[i]);
	scanf("%d", &Q);
	while(Q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		puts(lb[x] <= y && y <= rb[x] ? "YES" : "NO");
	}
	return 0;
}
