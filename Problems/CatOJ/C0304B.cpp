#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

int n;
char s[N];

std::vector<int> son[N];
int fa[N], another[N];
int match(int l) {
	if(s[l] == ')') return match(l + 1);
	int now = l + 1;
	while(now <= n && s[now] == '(') son[l].push_back(now), fa[now] = l, now = match(now) + 1;
	if(now <= n && s[now] == ')') another[l] = now, another[now] = l;
	return now;
}
LL out[N];
void calc(int u) {
	int sz = son[u].size();
	for(int i = 0; i < sz; i++) {
		out[son[u][i]] = (out[u] + (LL)(i + 1) * (sz - i)) % MOD;
		calc(son[u][i]);
	}
}

void solve(int l, int r) {
	son[0].clear();
	for(int i = l; i <= r; i++) out[i] = 0, fa[i] = 0, son[i].clear(), another[i] = 0;
	int now = l;
	while(now <= r) son[0].push_back(now), fa[now] = 0, now = match(now) + 1;
	calc(0);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 0; i <= n + 1; i++) out[i] = fa[i] = 0, son[i].clear(), another[i] = 0;
		int now = 1;
		while(now <= n) now = match(now) + 1;
		for(int i = 1; i <= n; ) {
			if(!another[i]) { i++; continue; }
			int j = i;
			while(j < n && another[j + 1]) j++;
			solve(i, j);
			i = j + 1;
		}
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += out[s[i] == ')' ? another[i] : i] * i % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}