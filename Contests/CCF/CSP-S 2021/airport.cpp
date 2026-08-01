#include <cstdio>
#include <algorithm>
#include <set>

const int N = 2e5 + 5;

struct Node { int v, id, t; } a[N], b[N];
bool operator<(Node x, Node y) { return x.v < y.v; }
int n, m, K;

int seata[N], seatb[N], ta[N], tb[N];
std::set<int> sta, stb;

int tmp[N];
void preprocess() {
	for(int i = 1; i <= 2 * n; i++) tmp[i] = a[i].v;
	std::sort(tmp + 1, tmp + 2 * n + 1);
	int n_ = std::unique(tmp + 1, tmp + 2 * n + 1) - tmp - 1;
	for(int i = 1; i <= 2 * n; i++) a[i].v = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i].v) - tmp;
	for(int i = 1; i <= 2 * m; i++) tmp[i] = b[i].v;
	std::sort(tmp + 1, tmp + 2 * m + 1);
	int m_ = std::unique(tmp + 1, tmp + 2 * m + 1) - tmp - 1;
	for(int i = 1; i <= 2 * m; i++) b[i].v = std::lower_bound(tmp + 1, tmp + m_ + 1, b[i].v) - tmp;
}

int main() {
	scanf("%d%d%d", &K, &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].v, &a[i + n].v), a[i].t = 1, a[i + n].t = 0, a[i].id = a[i + n].id = i;
	for(int i = 1; i <= m; i++) scanf("%d%d", &b[i].v, &b[i + m].v), b[i].t = 1, b[i + m].t = 0, b[i].id = b[i + m].id = i;
	preprocess();
	std::sort(a + 1, a + 2 * n + 1), std::sort(b + 1, b + 2 * m + 1);
	for(int i = 1; i <= K; i++) sta.insert(i), stb.insert(i);
	for(int i = 1; i <= 2 * n; i++)
		if(a[i].t == 1) {
			if(!sta.empty()) seata[a[i].id] = *sta.begin(), ta[seata[a[i].id]]++, sta.erase(sta.begin());
		} else {
			if(seata[a[i].id]) sta.insert(seata[a[i].id]);
		}
	for(int i = 1; i <= 2 * m; i++)
		if(b[i].t == 1) {
			if(!stb.empty()) seatb[b[i].id] = *stb.begin(), tb[seatb[b[i].id]]++, stb.erase(stb.begin());
		} else {
			if(seatb[b[i].id]) stb.insert(seatb[b[i].id]);
		}
	for(int i = 1; i <= K; i++) ta[i] += ta[i - 1], tb[i] += tb[i - 1];
	int ans = 0;
	for(int i = 0; i <= K; i++) ans = std::max(ans, ta[i] + tb[K - i]);
	printf("%d\n", ans);
	return 0;
}