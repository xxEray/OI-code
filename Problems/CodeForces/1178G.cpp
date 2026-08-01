#include <cstdio>
#include <algorithm>
#include <deque>
#include <cmath>

typedef long long LL;

const int N = 2e5 + 5;
const int SQRT_N = 900;

int n, Q;
LL a[N << 1], b[N << 1], tmpa[N], tmpb[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N], ek;
void add_edge(int u, int v) { edge[ek] = (Edge){v, head[u]}, head[u] = ek++; }

int t[N], ot[N], time_stamp;
void dfs(int u, int fa) {
	t[u] = ++time_stamp, a[u] += a[fa], b[u] += b[fa];
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) dfs(edge[i].to, u);
	ot[u] = time_stamp;
}

int B;
int blk[N << 1], id[N << 1];

LL coe[SQRT_N];
std::deque<int> q[SQRT_N];
bool compare(int i, int j, int k) {
	// ax+b=a'x+b'
	// x=(b'-b)/(a-a')
	// (b[j] - b[i]) / (a[i] - a[j]) >= (b[k] - b[j]) / (a[j] - a[k])
	return (b[j] - b[i]) * (a[j] - a[k]) >= (b[k] - b[j]) * (a[i] - a[j]);
}
void build(int l, int r) {
	r = std::min(r, n * 2);
	for(int i = l; i <= r; i++) b[i] += coe[blk[l]] * a[i];
	q[blk[l]].clear(), coe[blk[l]] = 0;
	for(int o = l; o <= r; o++) {
		int i = id[o];
		while(q[blk[l]].size() > 1 && compare(q[blk[l]].end()[-2], q[blk[l]].back(), i)) q[blk[l]].pop_back();
		q[blk[l]].push_back(i);
	}
	while(q[blk[l]].size() > 1 && b[q[blk[l]][0]] <= b[q[blk[l]][1]]) q[blk[l]].pop_front();
}
LL calc(LL k, int x) { return a[x] * k + b[x]; }
void modify(int l, int r, LL v) {
	if(blk[l] == blk[r]) {
		for(int i = l; i <= r; i++) b[i] += v * a[i];
		build((blk[l] - 1) * B + 1, blk[l] * B);
		return;
	}
	for(int i = l; i <= blk[l] * B; i++) b[i] += v * a[i];
	for(int i = (blk[r] - 1) * B + 1; i <= r; i++) b[i] += v * a[i];
	build((blk[l] - 1) * B + 1, blk[l] * B), build((blk[r] - 1) * B + 1, blk[r] * B);
	for(int i = blk[l] + 1; i <= blk[r] - 1; i++) {
		coe[i] += v;
		while(q[i].size() > 1 && a[q[i][0]] * coe[i] + b[q[i][0]] <= a[q[i][1]] * coe[i] + b[q[i][1]]) q[i].pop_front();
	}
}
LL query(int l, int r) {
	LL ans = 0;
	if(blk[l] == blk[r]) {
		build((blk[l] - 1) * B + 1, blk[l] * B);
		for(int i = l; i <= r; i++) ans = std::max(ans, b[i]);
		return ans;
	}
	build((blk[l] - 1) * B + 1, blk[l] * B), build((blk[r] - 1) * B + 1, blk[r] * B);
	for(int i = l; i <= blk[l] * B; i++) ans = std::max(ans, b[i]);
	for(int i = (blk[r] - 1) * B + 1; i <= r; i++) ans = std::max(ans, b[i]);
	for(int i = blk[l] + 1; i <= blk[r] - 1; i++) ans = std::max(ans, a[q[i][0]] * coe[i] + b[q[i][0]]);
	return ans;
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 2; i <= n; i++) { int u; scanf("%d", &u); add_edge(i, u), add_edge(u, i); }
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	dfs(1, 0);
	for(int i = 1; i <= n; i++) tmpa[i] = std::abs(b[i]), tmpb[i] = a[i] * std::abs(b[i]);
	for(int i = 1; i <= n; i++) a[t[i] * 2 - 1] = tmpa[i], b[t[i] * 2 - 1] = tmpb[i], a[t[i] * 2] = -tmpa[i], b[t[i] * 2] = -tmpb[i];
	B = sqrt(n * 2);
	for(int i = 1; i <= n * 2; i++) blk[i] = (i - 1) / B + 1;
	for(int i = 1; i <= blk[n * 2]; i++) {
		int l = (i - 1) * B + 1, r = std::min(i * B, n * 2);
		for(int j = l; j <= r; j++) id[j] = j;
		std::sort(id + l, id + r + 1, [&](int x, int y) { return a[x] < a[y]; });
		build(l, r);
	}
	while(Q--) {
		int type, x, v;
		scanf("%d", &type);
		if(type == 1) {
			scanf("%d%d", &x, &v);
			modify(t[x] * 2 - 1, ot[x] * 2, v);
		} else {
			scanf("%d", &x);
			printf("%lld\n", query(t[x] * 2 - 1, ot[x] * 2));
		}
	}
	return 0;
}