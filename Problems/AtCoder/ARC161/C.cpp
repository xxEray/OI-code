#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N], b[N];
std::vector<int> to[N];
bool f[N][2][2];

bool ans;
int ansid;
void dfs(int u, int fa) {
	int cnt[2] = {0, 0}, flag[2] = {1, 1};
	int son = 0;
	for(int v : to[u]) if(v != fa) {
		dfs(v, u);
		son++;
		for(int i = 0; i <= 1; i++)
			if(f[v][a[u]][i]) cnt[i]++;
			else if(!f[v][!a[u]][i]) flag[i] = 0;
	}
	if(u == 1) {
		if(flag[0] && cnt[0] > son / 2) ans = true, ansid = 0;
		if(flag[1] && cnt[1] > son / 2) ans = true, ansid = 1;
	} else {
		f[u][0][a[u]] = (flag[0] && cnt[0] + 1 > (son + 1) / 2), f[u][0][!a[u]] = (flag[0] && cnt[0] > (son + 1) / 2);
		f[u][1][a[u]] = (flag[1] && cnt[1] + 1 > (son + 1) / 2), f[u][1][!a[u]] = (flag[1] && cnt[1] > (son + 1) / 2);
	}
}

void get_answer(int u, int i, int fa) {
	b[u] = i;
	for(int v : to[u]) if(v != fa) {
		if(f[v][a[u]][i]) get_answer(v, a[u], u);
		else get_answer(v, !a[u], u);
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) to[i].clear(), f[i][0][0] = f[i][0][1] = f[i][1][0] = f[i][1][1] = false;
		for(int i = 1; i <= n; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), to[v].push_back(u); }
		for(int i = 1; i <= n; i++) { char str[2]; scanf("%1s", str); a[i] = (str[0] == 'W' ? 0 : 1); }
		ans = false;
		dfs(1, 0);
		if(ans) {
			get_answer(1, ansid, 0);
			for(int i = 1; i <= n; i++) putchar(b[i] ? 'B' : 'W');
			puts("");
		} else puts("-1");
	}
	return 0;
}