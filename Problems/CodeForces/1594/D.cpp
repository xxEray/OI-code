#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 5e5 + 5;

int n, m;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }
int cnt1[N], cnt2[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= 2 * n; i++) fa[i] = i;
		for(int i = 1; i <= m; i++) {
			char s[20];
			int x, y;
			scanf("%d%d%s", &x, &y, s);
			if(!strcmp(s, "imposter")) merge(x, y + n), merge(x + n, y);
			else merge(x, y), merge(x + n, y + n);
		}
		bool flag = false;
		for(int i = 1; i <= n; i++) if(find(i) == find(i + n)) { flag = true; break; }
		if(flag) puts("-1");
		else {
			for(int i = 1; i <= 2 * n; i++) cnt1[i] = cnt2[i] = 0;
			for(int i = 1; i <= n; i++) cnt1[find(i)]++, cnt2[find(i + n)]++;
			int ret = 0;
			for(int i = 1; i <= n; i++) ret += std::max(cnt1[i], cnt2[i]);
			printf("%d\n", ret);
		}
	}
	return 0;
}