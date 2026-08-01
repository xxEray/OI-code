#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 4000 + 5;

int n;
int a[N][N];
char str[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int sz[N], d[N], sum[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%s", str + 1);
			for(int j = 1; j <= n; j++) a[i][j] = str[j] - '0';
		}
		for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 0, d[i] = 0, sum[i] = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i][j]) merge(i, j), d[i]++;
		for(int i = 1; i <= n; i++) sz[find(i)]++;
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += find(i) == i;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i][j] && find(i) == find(j)) sum[find(i)]++;
		assert(cnt);
		if(cnt == 1) { puts("0"); continue; }
		int ans = 0;
		for(int i = 1; i <= n; i++) if(find(i) == i && (sz[i] == 1 || sum[i] < sz[i] * (sz[i] - 1))) {
			int id = 0;
			for(int j = 1; j <= n; j++) if(find(j) == i && (!id || d[id] > d[j])) id = j;
			ans = id;
			break;
		}
		if(ans) { printf("1\n%d\n", ans); continue; }
		assert(T != 771);
		if(cnt == 2) {
			int id = 0;
			for(int i = 1; i <= n; i++) if(find(i) == i && (!id || sz[i] < sz[id])) id = i;
			printf("%d\n", sz[id]);
			for(int i = 1; i <= n; i++) if(find(i) == id) printf("%d ", i);
			puts("");
		} else {
			int x = 0, y = 0;
			for(int i = 1; i <= n; i++) if(find(i) == i) { x = i; break; }
			for(int i = n; i >= 1; i--) if(find(i) == i) { y = i; break; }
			assert(x != y);
			printf("2\n%d %d\n", x, y);
		}
	}
	return 0;
}