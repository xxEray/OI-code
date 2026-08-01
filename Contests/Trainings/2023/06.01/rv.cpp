#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::rdc;
using FIO::wrtc;
using FIO::write;
using FIO::read;

const int N = 2000 + 5;

int n;
int a[N][N];

int b[N][N];
void broute_force() {
	int U = (1 << n) - 1;
	int ret[10] = {};
	for(int s = 0; s <= U; s++) {
		std::vector<int> vct;
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) vct.push_back(i);
		do {
			for(int i : vct) for(int j = 1; j <= n; j++) a[i][j] ^= 1, a[j][i] ^= 1;
			for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) b[i][j] = (i == j ? 1 : a[i][j]);
			for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) b[i][j] |= b[i][k] && b[k][j];
			bool flag = true;
			for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) flag &= b[i][j];
			if(flag) ret[__builtin_popcount(s)]++;
			for(int i : vct) for(int j = 1; j <= n; j++) a[i][j] ^= 1, a[j][i] ^= 1;
		} while(std::next_permutation(vct.begin(), vct.end()));
	}
	bool flag = false;
	for(int i = 0; i <= n; i++) if(ret[i]) { printf("%d %d\n", i, ret[i]); flag = true; break; }
	if(!flag) puts("-1");
}

int low[N], dfn[N], stk[N], vis[N], bl[N];
int time_stamp, top, scc;
void tarjan(int u) {
	low[u] = dfn[u] = ++time_stamp;
	stk[top++] = u;
	vis[u] = 1;
	for(int v = 1; v <= n; v++) if(a[u][v]) {
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
		} while(stk[top] != u);
	}
}
int d[N], t[N];
// std::vector<int> g[N];
// struct Compare { bool operator()(int x, int y) const { return d[x] == d[y] ? x < y : d[x] < d[y]; } };
void solve() {
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	if(scc == 1) { puts("0 1"); return; }
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i][j]) d[bl[i]]++;
	// for(int i = 1; i <= scc; i++) printf("%d ", d[i]);
	// puts("");`
	// std::set<int, Compare> st;
	// int sum = 0, target = scc * (scc - 1) / 2;
	// for(int i = 1; i <= scc; i++) st.insert(i), sum += d[i];
	// while(!st.empty() && sum > target) sum -= d[*st.rbegin()], st.erase(--st.end());
	// int ans = 0;
	// for(int i = 1; i <= n; i++) {
	// 	for(int j = 1; j <= n; j++) if(bl[i] != bl[j]) {
	// 		if(st.count(bl[i])) sum -= d[bl[i]], st.erase(bl[i]);
	// 		d[bl[i]] += (a[i][j] ? -1 : 1);
	// 		sum += d[bl[i]], st.insert(bl[i]);
	// 		if(sum > target) sum -= d[*st.rbegin()], st.erase(--st.end());
	// 		if(st.count(bl[j])) sum -= d[bl[j]], st.erase(bl[j]);
	// 		d[bl[j]] += (a[i][j] ? 1 : -1);
	// 		sum += d[bl[j]], st.insert(bl[j]);
	// 		if(sum > target) sum -= d[*st.rbegin()], st.erase(--st.end());
	// 	}
	// 	if(sum != target) ans++;
	// 	for(int j = 1; j <= n; j++) if(bl[i] != bl[j]) {
	// 		if(st.count(bl[i])) sum -= d[bl[i]], st.erase(bl[i]);
	// 		d[bl[i]] += (a[i][j] ? 1 : -1);
	// 		sum += d[bl[i]], st.insert(bl[i]);
	// 		if(sum > target) sum -= d[*st.rbegin()], st.erase(--st.end());
	// 		if(st.count(bl[j])) sum -= d[bl[j]], st.erase(bl[j]);
	// 		d[bl[j]] += (a[i][j] ? -1 : 1);
	// 		sum += d[bl[j]], st.insert(bl[j]);
	// 		if(sum > target) sum -= d[*st.rbegin()], st.erase(--st.end());
	// 	}
	// }
	// printf("1 %d\n", ans);
	for(int i = 1; i <= n; i++) d[i] = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i][j]) d[i]++;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) if(i != j) d[i] += (a[i][j] ? -1 : 1), d[j] += (a[i][j] ? 1 : -1);
		for(int j = 1; j <= n; j++) t[j] = d[j];
		// for(int j = 1; j <= n; j++) printf("%d ", t[j]);
		// puts("");
		std::sort(t + 1, t + n + 1);
		int sum = 0;
		bool flag = true;
		for(int j = 1; j < n; j++) sum += t[j], flag &= (sum != j * (j - 1) / 2);
		ans += flag;
		for(int j = 1; j <= n; j++) if(i != j) d[i] += (a[i][j] ? 1 : -1), d[j] += (a[i][j] ? -1 : 1);
	}
	printf("1 %d\n", ans);
}

int main() {
	FIO::read(n);
	for(int i = 1; i <= n; i++) {
		char c = FIO::rdc();
		while(c != '0' && c != '1') c = FIO::rdc();
		a[i][1] = c - '0';
		for(int j = 2; j <= n; j++) a[i][j] = FIO::rdc() - '0';
	}
	if(n <= 6) broute_force();
	else solve();
	return 0;
}