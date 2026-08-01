#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 1000 + 5;

int n;
int d[N], order[N];

int fa[N], val[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int ask(int u) {
	printf("? %d\n", u);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
		for(int i = 1; i <= n; i++) fa[i] = i, val[i] = 0, order[i] = i;
		std::sort(order + 1, order + n + 1, [&](int x, int y) { return d[x] > d[y]; });
		for(int o = 1; o <= n; o++) {
			int i = order[o], cnt = d[i];
			while(!val[find(i)] && cnt--) {
				int j = ask(i);
				merge(i, j);
			}
			val[find(i)] = 1;
		}
		printf("! ");
		for(int i = 1; i <= n; i++) printf("%d ", find(i));
		puts("");
		fflush(stdout);
	}
	return 0;
}