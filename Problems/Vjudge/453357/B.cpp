#include <cstdio>
#include <algorithm>
#include <map>

const int N = 1e5 + 5;

int a[N], b[N];
int n;

int cla[N], clb[N];
std::map<int, int> id;
int cid;

int fa[N], size[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

bool check(int i) { return a[i] != b[i] || i == n + 1; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cla[i] = a[i], cla[n + 1] ^= a[i];
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), clb[i] = b[i], clb[n + 1] ^= b[i];
	a[n + 1] = cla[n + 1], b[n + 1] = clb[n + 1];
	std::sort(cla + 1, cla + n + 2);
	std::sort(clb + 1, clb + n + 2);
	for(int i = 1; i <= n + 1; i++) if(cla[i] != clb[i]) { puts("-1"); return 0; }
	int ans = 0;
	for(int i = 1; i <= n + 1; i++) if(check(i) && id.find(a[i]) == id.end()) id[a[i]] = ++cid;
	for(int i = 1; i <= n + 1; i++) if(check(i) && id.find(b[i]) == id.end()) id[b[i]] = ++cid;
	for(int i = 1; i <= n; i++) ans += (a[i] != b[i]);
	for(int i = 1; i <= cid; i++) fa[i] = i;
	for(int i = 1; i <= n + 1; i++) if(check(i)) merge(id[a[i]], id[b[i]]);
	for(int i = 1; i <= cid; i++) if(find(i) == i) ans++;
	printf("%d\n", ans ? ans - 1 : 0);
	return 0;
} /*
3
0 1 2 3
3 1 0 2

0 1 2 3 0
1 0 3 2 0

*/