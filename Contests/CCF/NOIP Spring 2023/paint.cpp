#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, m, Q;

int rc[N], rt[N], cc[N], ct[N];

int main() {
// #ifndef DEBUG
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
// #endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n; i++) rc[i] = rt[i] = 0;
		for(int i = 1; i <= m; i++) cc[i] = ct[i] = 0;
		for(int q = 1; q <= Q; q++) {
			int opt, x, c;
			scanf("%d%d%d", &opt, &x, &c);
			if(opt == 0) rc[x] = c, rt[x] = q;
			else cc[x] = c, ct[x] = q;
		}
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d%c", rt[i] > ct[j] ? rc[i] : cc[j], j == m ? '\n' : ' ');
	}
	return 0;
}