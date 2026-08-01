#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 100 + 5;

int a[N];
int n;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n * 2; i++) fa[i] = i;
		for(int i = 1; i <= n; i++) {
			int j = i == n ? 1 : i + 1;
			if(s[i] == 'E') merge(i, j);
			// else merge(i, j + n), merge(i + n, j);
		}
		bool flag = true;
		for(int i = 1; i <= n; i++) if(s[i] == 'N' && find(i) == find(i % n + 1)) flag = false;
		puts(flag ? "YES" : "NO");
	}
	return 0;
}