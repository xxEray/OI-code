#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int q[N][3];
int n;

int tmp[N << 1];
int m;
void discrete() {
	m = 0;
    for(int i = 1; i <= n; i++) tmp[++m] = q[i][0], tmp[++m] = q[i][1];
    std::sort(tmp + 1, tmp + m + 1);
    m = std::unique(tmp + 1, tmp + m + 1) - tmp - 1;
    for(int i = 1; i <= n; i++) {
		q[i][0] = std::lower_bound(tmp + 1, tmp + m + 1, q[i][0]) - tmp;
		q[i][1] = std::lower_bound(tmp + 1, tmp + m + 1, q[i][1]) - tmp;
	}
}

int fa[N << 1];
void init(int mx) { for(int i = 1; i <= mx; i++) fa[i] = i; }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d%d%d", &q[i][0], &q[i][1], &q[i][2]);
        discrete();
        init(m);
		bool flag = true;
		for(int i = 1; i <= n; i++) if(q[i][2]) merge(q[i][0], q[i][1]);
		for(int i = 1; i <= n; i++) if(!q[i][2]) flag &= find(q[i][0]) != find(q[i][1]);
		puts(flag ? "YES" : "NO");
    }
    return 0;
}