#include <bits/stdc++.h>

const int N = 4e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
char s[N];

int dot[N], id[N], fa[N], dep[N];
std::vector<int> son[N];

int parse() {
	static int p = 1, cdot = 0;
	int u = ++cdot;
	assert(s[p] == '(');
	dot[p] = u, p++;
	while(s[p] == '(') {
		int v = parse();
		id[v] = son[u].size();
		fa[v] = u, son[u].push_back(v);
	}
	assert(s[p] == ')');
	dot[p] = u, p++;
	return u;
}

struct DP { int a[2][2]; } init;
DP f[N];
DP calc(DP x, DP y) {
	DP z;
	z.a[0][0] = std::min(x.a[0][0] + y.a[0][0], x.a[0][1] + y.a[1][0]);
	z.a[0][1] = std::min(x.a[0][0] + y.a[0][1], x.a[0][1] + y.a[1][1]);
	z.a[1][0] = std::min(x.a[1][0] + y.a[0][0], x.a[1][1] + y.a[1][0]);
	z.a[1][1] = std::min(x.a[1][0] + y.a[0][1], x.a[1][1] + y.a[1][1]);
	return z;
}

int go[20][N];
DP gof[20][N];
void preprocess() {
	for(int i = 1; i <= n; i++) go[0][i] = fa[i], gof[0][i] = f[i];
	for(int j = 1; j < 20; j++)
		for(int i = 1; i <= n; i++) {
			go[j][i] = go[j - 1][go[j - 1][i]];
			gof[j][i] = calc(gof[j - 1][i], gof[j - 1][go[j - 1][i]]);
		}
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) std::swap(u, v);
	for(int j = 0; j < 20; j++) if((dep[u] - dep[v]) >> j & 1) u = go[j][u];
	if(u == v) return u;
	for(int j = 19; j >= 0; j--) if(go[j][u] != go[j][v]) u = go[j][u], v = go[j][v];
	return fa[u];
}

int main() {
#ifndef DEBUG
	freopen("percent.in", "r", stdin);
	freopen("percent.out", "w", stdout);
#endif
	scanf("%s%d", s + 2, &Q);
	n = strlen(s + 2);
	s[1] = '(', s[n + 2] = ')';
	n += 2;
	parse();
//	printf("dot: "); for(int i = 1; i <= n; i++) printf("%d ", dot[i]); puts("");
//	for(int i = 1; i <= n / 2; i++) {
//		printf("%d: id=%d, fa=%d, dep=%d, son=", i, id[i], fa[i], dep[i]);
//		for(int v : son[i]) printf("%d ", v);
//		puts("");
//	}
	init.a[0][0] = init.a[1][1] = 0, init.a[0][1] = init.a[1][0] = 1;
	for(int i = 1; i <= n / 2; i++) dep[i] = dep[fa[i]] + 1;
	for(int i = 2; i <= n / 2; i++) {
		int sz = son[fa[i]].size();
		f[i].a[0][0] = 2 * id[i] + 1, f[i].a[1][1] = 2 * (sz - id[i] - 1) + 1;
		f[i].a[0][0] = std::min(f[i].a[0][0], f[i].a[1][1] + 2), f[i].a[1][1] = std::min(f[i].a[1][1], f[i].a[0][0] + 2);
		f[i].a[0][1] = std::min(f[i].a[0][0], f[i].a[1][1]) + 1, f[i].a[1][0] = std::min(f[i].a[0][0], f[i].a[1][1]) + 1;
		// printf("f[%d]: %d %d %d %d\n", i, f[i].a[0][0], f[i].a[0][1], f[i].a[1][0], f[i].a[1][1]);
	}
	preprocess();
	while(Q--) {
		int p, q;
		scanf("%d%d", &p, &q);
		p++, q++;
		int u = dot[p], v = dot[q], iu = (s[p] == ')'), iv = (s[q] == ')');
		int ff = lca(u, v);
		// printf("u = %d, v = %d, lca = %d\n", u, v, ff);
		if(u == ff || v == ff) {
			if(v == ff) std::swap(u, v), std::swap(iu, iv);
			DP fv = init;
			for(int j = 0; j < 20; j++) if((dep[v] - dep[u]) >> j & 1) fv = calc(fv, gof[j][v]), v = go[j][v];
			// printf("f: %d %d %d %d\n", fv.a[0][0], fv.a[0][1], fv.a[1][0], fv.a[1][1]);
			printf("%d\n", fv.a[iv][iu]);
			continue;
		}
		DP fu = init, fv = init;
		for(int j = 0; j < 20; j++) {
			if((dep[u] - dep[ff] - 1) >> j & 1) fu = calc(fu, gof[j][u]), u = go[j][u];
			if((dep[v] - dep[ff] - 1) >> j & 1) fv = calc(fv, gof[j][v]), v = go[j][v];
		}
		assert(u != v);
		if(id[u] > id[v]) std::swap(u, v), std::swap(fu, fv), std::swap(iu, iv);
		int ans1 = fu.a[iu][1] + fv.a[iv][0] + 2 * (id[v] - id[u] - 1) + 1;
		int ans2 = ff == 1 ? INF : calc(fu, f[u]).a[iu][0] + calc(fv, f[v]).a[iv][1] + 1;
		printf("%d\n", std::min(ans1, ans2));
	}
	return 0;
}