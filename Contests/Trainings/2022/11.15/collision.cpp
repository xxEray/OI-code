#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

#define SZ(x) ((int)(x).size())

int n;
LL L, R;
int x[N], p[N], q[N], v[N], id[N], ox[N];
std::vector<int> a, b;

LL tmp[N];
void discrete() {
	int c = 0;
	for(int i = 1; i <= n; i++) tmp[++c] = x[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) p[i] = std::lower_bound(tmp + 1, tmp + c + 1, x[i]) - tmp;
}
struct Node { int v, id; } tmp2[N];
bool operator<(Node i, Node j) { return i.v == j.v ? ox[i.id] > ox[j.id] : i.v < j.v; }
void discrete2() {
	for(int i = 1; i <= n; i++) tmp2[i] = (Node){x[i], i};
	std::sort(tmp2 + 1, tmp2 + n + 1);
	for(int i = 1; i <= n; i++) x[tmp2[i].id] = i;
}

LL count(int lim) {
	LL ret = 0;
	for(int i = 0, j = 0, k = 0; j < SZ(b); j++) {
		while(k < SZ(a) && x[b[j]] > x[a[k]]) k++;
		while(i < SZ(a) && x[b[j]] - x[a[i]] > lim) i++;
		ret += k - i;
	}
	return ret;
}

std::vector<std::array<int, 3>> ans, out;
void solve(int liml, int limr) {
	for(int il = 0, ir = 0, j = 0; j < SZ(b); j++) {
		while(il < SZ(a) && x[b[j]] - x[a[il]] > liml) il++;
		while(ir < SZ(a) && x[b[j]] - x[a[ir]] > limr) ir++;
		for(int k = ir; k < il; k++) ans.push_back({x[b[j]] - x[a[k]], a[k], b[j]});
	}
}

int calc(LL v) {
	LL l = 0, r = 1e9 + 1;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(count(mid) < v) l = mid + 1;
		else r = mid;
	}
	return l - 1;
}

int main() {
#ifndef DEBUG
	freopen("collision.in", "r", stdin);
	freopen("collision.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &x[i], &v[i]);
		(v[i] == 1 ? a : b).push_back(i);
	}
	scanf("%lld%lld", &L, &R);
	discrete();
	for(int i = 1; i <= n; i++) q[p[i]] = i;
	std::sort(a.begin(), a.end(), [&](int i, int j) { return x[i] < x[j]; });
	std::sort(b.begin(), b.end(), [&](int i, int j) { return x[i] < x[j]; });
	int dl = calc(L), dr = calc(R);
	dl -= dl & 1;
	solve(dl, dr + 1);
	std::sort(ans.begin(), ans.end());
//	for(auto p : ans) printf("t=%d/2, %d <-> %d\n", p[0], p[1], p[2]);
	LL base = count(dl);
	L -= base, R -= base;
//	printf("dl = %d\n", dl);
	for(int i = 1; i <= n; i++) ox[i] = x[i], x[i] += dl / 2 * v[i];
	discrete2();
	for(int i = 1; i <= n; i++) id[i] = q[x[i]];
//	for(int i = 1; i <= n; i++) printf("%d ", id[i]);
//	puts("");
	for(auto &i : ans) out.push_back({i[0], id[i[1]], id[i[2]]}), std::swap(id[i[1]], id[i[2]]);
	std::sort(out.begin(), out.end());
	for(int i = L - 1; i < R; i++) printf("%d %d\n", out[i][1], out[i][2]);
	return 0;
}
