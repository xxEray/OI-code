#include <cstdio>
#include <algorithm>
#include <cassert>

typedef unsigned long long LL;

const int N = 2.5e5 + 5;
const int SQRT_N = 1000 + 5;

int n, m;
LL a[2][N];
struct Query { int l, r, id; } q[N];
bool operator<(Query x, Query y) { return x.r < y.r; }
LL out[N];

const int blocksz = 300;
inline int block(int i) { return (i - 1) / blocksz + 1; }
inline int blkl(int x) { return (x - 1) * blocksz + 1; }
inline int blkr(int x) { return std::min(n, x * blocksz); }

LL b[2][N], c[N];
LL sumb[2][2][SQRT_N], sumc[SQRT_N];
LL tagb[2][SQRT_N], tagc[SQRT_N];
bool same[2][SQRT_N];

void pushdown(int x) {
	if(same[0][x]) for(int i = blkl(x); i <= blkr(x); i++) b[0][i] = tagb[0][x];
	if(same[1][x]) for(int i = blkl(x); i <= blkr(x); i++) b[1][i] = tagb[1][x];
	for(int i = blkl(x); i <= blkr(x); i++) c[i] += tagc[x] * (same[0][x] ? 1 : b[0][i]) * (same[1][x] ? 1 : b[1][i]);
	tagc[x] = 0;
}
void pushup(int x) {
	sumb[0][0][x] = sumb[0][1][x] = sumb[1][0][x] = sumb[1][1][x] = sumc[x] = 0;
	for(int i = blkl(x); i <= blkr(x); i++) sumb[1][1][x] += 1, sumb[1][0][x] += b[1][i], sumb[0][1][x] += b[0][i], sumb[0][0][x] += b[0][i] * b[1][i], sumc[x] += c[i];
}
void modifyb(int id, int l, int r, int v) {
	// /* purpose: */ for(int i = l; i <= r; i++) b[id][i] = v; return;
	if(block(l) == block(r)) {
		pushdown(block(l));
		same[id][block(l)] = false;
		for(int i = l; i <= r; i++) b[id][i] = v;
		pushup(block(l));
	} else {
		for(int x = block(l) + 1; x <= block(r) - 1; x++) {
			if(!same[id][x]) pushdown(x), same[id][x] = true, pushup(x);
			tagb[id][x] = v;
		}
		pushdown(block(l)), pushdown(block(r));
		same[id][block(l)] = same[id][block(r)] = false;
		for(int i = l; i <= blkr(block(l)); i++) b[id][i] = v;
		for(int i = blkl(block(r)); i <= r; i++) b[id][i] = v;
		pushup(block(l)), pushup(block(r));
	}
}
void modifyc(int l, int r) {
	// /* purpose: */ for(int i = l; i <= r; i++) c[i] += b[0][i] * b[1][i]; return;
	if(block(l) == block(r)) {
		pushdown(block(l));
		for(int i = l; i <= r; i++) c[i] += b[0][i] * b[1][i];
		pushup(block(l));
	} else {
		for(int x = block(l) + 1; x <= block(r) - 1; x++) tagc[x] += (same[0][x] ? tagb[0][x] : 1) * (same[1][x] ? tagb[1][x] : 1);
		pushdown(block(l)), pushdown(block(r));
		for(int i = l; i <= blkr(block(l)); i++) c[i] += b[0][i] * b[1][i];
		for(int i = blkl(block(r)); i <= r; i++) c[i] += b[0][i] * b[1][i];
		pushup(block(l)), pushup(block(r));
	}
}
LL queryb(int id, int i) {
	// /* purpose: */ return b[id][i];
	return same[id][block(i)] ? tagb[id][block(i)] : b[id][i];
}
LL queryc(int l, int r) {
	// /* purpose: */ LL sm = 0; for(int i = l; i <= r; i++) sm += c[i]; return sm;
	LL sum = 0;
	if(block(l) == block(r)) {
		pushdown(block(l));
		for(int i = l; i <= r; i++) sum += c[i];
		pushup(block(l));
	} else {
		for(int x = block(l) + 1; x <= block(r) - 1; x++) sum += sumc[x] + tagc[x] * sumb[same[0][x]][same[1][x]][x];
		pushdown(block(l)), pushdown(block(r));
		for(int i = l; i <= blkr(block(l)); i++) sum += c[i];
		for(int i = blkl(block(r)); i <= r; i++) sum += c[i];
		pushup(block(l)), pushup(block(r));
	}
	return sum;
}

void solve(int id, int i) {
	int x, j;
	for(x = block(i - 1); x > 1; x--) if(queryb(id, blkl(x)) >= a[id][i]) break;
	for(j = blkl(x); queryb(id, j) >= a[id][i]; j++);
	modifyb(id, j, i, a[id][i]);
}

int main() {
	scanf("%*d%d", &n);
	// while(blocksz * blocksz <= n) blocksz++;
	for(int i = 1; i <= n; i++) scanf("%llu", &a[0][i]);
	for(int i = 1; i <= n; i++) scanf("%llu", &a[1][i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	int p = 1;
	for(int i = 1; i <= n; i++) {
		solve(0, i), solve(1, i);
		modifyc(1, i);
		while(p <= m && q[p].r == i) out[q[p].id] = queryc(q[p].l, q[p].r), p++;
	}
	for(int i = 1; i <= m; i++) printf("%llu\n", out[i]);
	return 0;
}