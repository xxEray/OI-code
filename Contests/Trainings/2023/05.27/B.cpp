#include <bits/stdc++.h>

const int N = 20 + 3;
const int INF = 0x3f3f3f3f;
const int MAXS = (1 << 20) + 5;

int n;
int a[N], b[N];
char tmp[N];

int c[2], d[N];

std::vector<int> inside[MAXS];

int q[2][N];

int main() {
    // freopen("b.in", "r", stdin);
    // freopen("b.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		scanf("%s", tmp + 1);
		for(int i = 1; i <= n; i++) a[i] = (tmp[i] == 'Y' ? 1 : 0);
		for(int i = 1; i <= n; i++) {
			scanf("%s", tmp + 1);
			b[i] = 0;
			for(int j = 1; j <= n; j++) b[i] |= (tmp[j] == 'Y' ? 1 : 0) << (j - 1);
		}
		for(int i = 1; i <= n; i++) b[i] &= ~(1 << (i - 1));
		int ans = INF, U = (1 << n) - 1;
		for(int s = 0; s <= U; s++) {
			// printf("s = %d\n", s);
			int hd[2] = {1, 1}, tl[2] = {1, 1};
			int cnt = 0;
			c[0] = c[1] = 0;
			for(int i = 1; i <= n; i++) {
				if(a[i]) c[0] |= (1 << (i - 1)), c[1] |= (1 << (i - 1));
				d[i] = 0;
				cnt += a[i];
				if(a[i]) {
					int t = s >> (i - 1) & 1;
					q[t][tl[t]++] = i;
				}
			}
			if(cnt == n) { ans = 0; break; }
			for(int i = 1; i <= std::min(ans, n + 1); i++) {
				int stp[2] = {tl[0], tl[1]};
				while(hd[0] < stp[0]) {
					int u = q[0][hd[0]++];
					d[u]++;
					for(int msk = (b[u] & ~c[0]); msk; msk = (msk & (msk - 1))) {
						int v = __builtin_ctz(msk) + 1;
						c[0] |= (1 << (v - 1));
						if((c[1] >> (v - 1) & 1)) cnt++;
						if((d[v] ^ (s >> (v - 1) & 1)) == 0) q[0][tl[0]++] = v;
					}
					if(d[u] == 1 && (c[1] >> (u - 1) & 1)) q[1][tl[1]++] = u;
				}
				while(hd[1] < stp[1]) {
					int u = q[1][hd[1]++];
					d[u]++;
					for(int msk = (b[u] & ~c[1]); msk; msk = (msk & (msk - 1))) {
						int v = __builtin_ctz(msk) + 1;
						c[1] |= (1 << (v - 1));
						if((c[0] >> (v - 1) & 1)) cnt++;
						if((d[v] ^ (s >> (v - 1) & 1)) == 1) q[1][tl[1]++] = v;
					}
					if(d[u] == 1 && (c[1] >> (u - 1) & 1)) q[0][tl[0]++] = u;
				}
				// printf("%d: ", i); for(int j = 1; j <= n; j++) printf("%d ", (c[0] >> (j - 1) & 1) | ((c[1] >> (j - 1) & 1) << 1)); puts("");
				if(cnt == n) { ans = std::min(ans, i); break; }
			}
		}
		printf("%d\n", ans == INF ? -1 : ans);
	}
	return 0;
} /*
2
3
YNN
NYN
NNY
NNN
6
YYYYYN
NYYYYN
YNYYYN
YYNYYN
YYYNYN
YYYYNN
NNNNNN
*/