#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;
struct Node { int val; LL cnt; } a[N], b[N];

std::vector<LL> vct;

int main() {
#ifndef DEBUG
	freopen("fullmoon.in", "r", stdin);
	freopen("fullmoon.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d%lld", &a[i].val, &a[i].cnt);
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) scanf("%d%lld", &b[i].val, &b[i].cnt);
		LL sum = 0, sum0 = 0;
		for(int i = 1; i <= n; i++) sum += a[i].val * a[i].cnt - b[i].val * b[i].cnt, sum0 += a[i].val * a[i].cnt;
		if(sum != 0) { puts("0"); continue; }
		if(n == 1 && m == 1) { puts("1"); continue; }
		if(sum0 >= 1000000) { puts("1"); continue; }
		vct.clear();
		for(int i = 1; i <= m; i++) while(b[i].cnt--) vct.push_back(b[i].val);
		for(int i = 1; i <= n; i++) while(a[i].cnt--) {
			std::sort(vct.begin(), vct.end(), std::greater<int>());
			while(!vct.empty() && vct.back() == 0) vct.pop_back();
			if((int)vct.size() < a[i].val) { puts("0"); goto _End_; }
			for(int j = 0; j < a[i].val; j++) vct[j]--;
		}
		puts("1");
		_End_: continue;
	}
	return 0;
}