#include <bits/stdc++.h>

const int N = 6e5 + 5;

int n, Q;

int c[N * 31][2], tag[N * 31], cnt[N * 31];
int tot = 1;
int nw() { return ++tot; }
void settag(int x, int v) {
	if(!x) return;
	if(v & 1) std::swap(c[x][0], c[x][1]);
	tag[x] ^= v;
}
void pushdown(int x) {
	assert(x);
	settag(c[x][0], tag[x] >> 1), settag(c[x][1], tag[x] >> 1);
	tag[x] = 0;
}
void insert(int v) {
	int x = 1;
	for(int i = 0; i <= 29; i++) {
		pushdown(x);
		if(!c[x][v >> i & 1]) c[x][v >> i & 1] = nw();
		x = c[x][v >> i & 1];
	}
	cnt[x]++;
}
void erase(int v) {
	int x = 1;
	for(int i = 0; i <= 29; i++) {
		assert(x);
		pushdown(x);
		x = c[x][v >> i & 1];
	}
	cnt[x]--;
}
void incall() {
	int x = 1;
	for(int i = 0; i <= 29; i++) {
		if(!x) break;
		pushdown(x);
		std::swap(c[x][0], c[x][1]);
		x = c[x][0];
	}
}
void xorall(int v) {
	settag(1, v);
}

std::vector<int> ans;
void dfs(int x, int d, int v) {
	if(!x) return;
	pushdown(x);
	if(d == 29) {
		while(cnt[x]--) ans.push_back(v);
		return;
	}
	dfs(c[x][0], d + 1, v), dfs(c[x][1], d + 1, v | (1 << (d + 1)));
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); insert(x); }
	while(Q--) {
		int t, v;
		scanf("%d", &t);
		if(t == 1) scanf("%d", &v), insert(v);
		else if(t == 2) scanf("%d", &v), erase(v);
		else if(t == 3) incall();
		else if(t == 4) scanf("%d", &v), xorall(v);
	}
	dfs(1, -1, 0);
	std::sort(ans.begin(), ans.end());
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
} /*
2 4
5 10
3
1 6
4 2
2 4
*/