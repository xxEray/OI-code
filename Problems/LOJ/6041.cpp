#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>

const int N = 1e5 + 5;

int n, m;
char s[N];
struct Query { int l, r, id; } q[N];

int blksz;
int block(int i) { return (i - 1) / blksz + 1; }
int blkl(int x) { return (x - 1) * blksz + 1; }

int sa[N << 1], rk[N << 1], ht[N];
void init_SA() {
	static int tot[N], tp[N];
	int cs = '1';
	for(int i = 0, p = 0; p < n; i = (i ? i << 1 : 1), cs = p) {
		if(i) {
			p = 0;
			for(int j = 1; j <= i; j++) tp[++p] = n - i + j;
			for(int j = 1; j <= n; j++) if(sa[j] > i) tp[++p] = sa[j] - i;
		} else for(int j = 1; j <= n; j++) rk[j] = s[j], tp[j] = j;
		for(int j = 0; j <= cs; j++) tot[j] = 0;
		for(int j = 1; j <= n; j++) tot[rk[j]]++;
		for(int j = 0; j <= cs; j++) tot[j] += tot[j - 1];
		for(int j = n; j >= 1; j--) sa[tot[rk[tp[j]]]--] = tp[j];
		if(!i) continue;
		for(int j = 1; j <= n; j++) tp[j] = rk[j];
		rk[sa[1]] = p = 1;
		for(int j = 2; j <= n; j++) rk[sa[j]] = ((tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i]) ? p : ++p);
	}
	for(int i = 1, k = 0; i <= n; i++) {
		if(rk[i] == 1) { ht[rk[i]] = 0; continue; }
		if(k) k--;
		int j = sa[rk[i] - 1];
		while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}

int lg[N];
int gomx[21][N];
void init_ST() {
	lg[0] = -1;
	for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= n; i++) gomx[0][i] = ht[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= n; i++)
			gomx[j][i] = std::min(gomx[j - 1][i], gomx[j - 1][i + (1 << (j - 1))]);
}
int min_of(int l, int r) {
	int k = lg[r - l + 1];
	return std::min(gomx[k][l], gomx[k][r - (1 << k) + 1]);
}

int ans;
bool tick[N];
int prv[N], nxt[N];
int tot[N], tprv[N], tnxt[N];
std::vector<std::array<int, 3>> op;
void init(int l, int r) {
	ans = 0;
	op.clear();
	for(int i = 0; i <= n; i++) tick[i] = false, prv[i] = nxt[i] = 0, tprv[i] = tnxt[i] = 0, tot[i] = 0;
	for(int i = l; i <= r; i++) tick[rk[i]] = true;
	int last = 0;
	for(int i = 1; i <= n; i++) if(tick[i]) prv[i] = last, last = i;
	last = 0;
	for(int i = n; i >= 1; i--) if(tick[i]) nxt[i] = last, last = i;
	for(int i = 1; i <= n; i++) if(tick[i] && nxt[i]) {
		int v = min_of(i + 1, nxt[i]);
		tot[v]++;
	}
	last = 0;
	for(int i = 0; i <= n; i++) if(tot[i]) tprv[i] = last, last = i;
	last = 0;
	for(int i = n; i >= 0; i--) if(tot[i]) tnxt[i] = last, last = i;
	for(int i = 0; i <= n; i++) if(tot[i]) ans = i;
}
void del(int i) {
	i = rk[i];
	tick[i] = false;
	op.push_back({i, 0, ans});
	if(prv[i] || nxt[i]) {
		int v;
		if(!prv[i]) v = min_of(i + 1, nxt[i]);
		else if(!nxt[i]) v = min_of(prv[i] + 1, i);
		else v = std::max(min_of(prv[i] + 1, i), min_of(i + 1, nxt[i]));
		op.back()[1] = v;
		tot[v]--;
		if(!tot[v]) {
			if(ans == v) ans = tprv[v];
			tnxt[tprv[v]] = tnxt[v], tprv[tnxt[v]] = tprv[v];
		}
	}
	nxt[prv[i]] = nxt[i], prv[nxt[i]] = prv[i];
}
void undo() {
	int i = op.back()[0];
	ans = op.back()[2];
	tick[i] = true;
	if(prv[i] || nxt[i]) {
		int v = op.back()[1];
		tot[v]++;
		if(tot[v] == 1) tnxt[tprv[v]] = v, tprv[tnxt[v]] = v;
	}
	nxt[prv[i]] = i, prv[nxt[i]] = i;
	op.pop_back();
}
int answer() { return ans; }

int out[N];

int main() {
	scanf("%d%d%s", &n, &m, s + 1);
	std::reverse(s + 1, s + n + 1);
	while((long long)blksz * blksz < n) blksz++;
	init_SA();
	init_ST();
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
		q[i].l = n - q[i].l + 1, q[i].r = n - q[i].r + 1, std::swap(q[i].l, q[i].r);
	}
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return block(x.l) == block(y.l) ? x.r > y.r : block(x.l) < block(y.l); });
	int j = 1;
	for(int x = 1; x <= block(n); x++) {
		init(blkl(x), n);
		int lb = blkl(x), rb = n;
		while(j <= m && block(q[j].l) == x) {
			while(rb > q[j].r) del(rb--);
			while(lb < q[j].l) del(lb++);
			out[q[j].id] = answer();
			while(lb > blkl(x)) lb--, undo();
			j++;
		}
	}
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
}