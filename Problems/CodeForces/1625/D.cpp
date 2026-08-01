#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 3e5 + 5;

struct Node { int val, id; operator int() { return val; } } a[N];
bool operator<(Node x, Node y) { return x.val < y.val; }
int n, m, bitm;

int c[N * 30][2], end[N * 30];
int cn;

bool ok[N];
int dfs(int l, int r, int bit) {
	if(l > r || bit < 0) return 0;
	int v = a[l] >> bit << bit;
	int bd = std::lower_bound(a + l, a + r + 1, v + (1 << (bit - 1))) - a - 1;
	int ret = 0, ind1, ind2, fl = 0;
	memset(c, 0, sizeof(int) * (r - l + 2) * 60);
	memset(end, 0, sizeof(int) * (r - l + 2) * 30);
	cn = 0;
	for(int i = l; i <= r; i++) {
		int now = 0;
		for(int j = 30; j >= 0; j--) {
			int bt = a[i] >> j & 1;
			if(!c[now][bt]) c[now][bt] = ++cn;
			now = c[now][bt];
		}
		end[now] = i;
	}
	for(int i = l; i <= r; i++) {
		int now = 0;
		for(int j = 30; j >= 0; j--) {
			int bt = a[i] >> j & 1;
			if(!c[now][!bt]) now = c[now][bt];
			else now = c[now][!bt];
		}
		if((a[i] ^ a[end[now]]) >= m) { ind1 = i, ind2 = end[now], fl = 1; break; }
	}
	if(m & (1 << bit)) {
		if(fl) ok[ind1] = ok[ind2] = true, ret = 2;
	} else {
		int ret1 = dfs(l, bd, bit - 1), ret2 = dfs(bd + 1, r, bit - 1);
		ret = 0;
		if(bd >= l && bd < r) {
			if((a[l] ^ a[r]) >= m) {
				if(!ret1) ret1 = 1, ok[l] = true;
				if(!ret2) ret2 = 1, ok[r] = true;
			} else if(!ret1 && !ret2) { if(fl) ok[ind1] = ok[ind2] = true, ret1 = 2; }
		}
		ret += ret1 + ret2;
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].id = i;
	if(m == 0) { printf("%d\n", n); for(int i = 1; i <= n; i++) printf("%d ", i); return 0; }
	std::sort(a + 1, a + n + 1);
	while((1 << bitm) < m) bitm++;
	int cnt = dfs(1, n, 30);
	if(cnt <= 1) { puts("-1"); return 0; }
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) if(ok[i]) printf("%d ", a[i].id);
	return 0;
} /*
6 15
2 8 4 12 4 8
*/