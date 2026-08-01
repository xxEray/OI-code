#include <cstdio>
#include <algorithm>

const int N = 5000 + 5;
const int INF = 0x3f3f3f3f;

int n, cnt[3];
int a[N], b[N];
int mn1[N][2], mn2[N][2], mn3[N], mn4[N];

int pre[2][N];
void preprocess() {
	cnt[0] = cnt[1] = cnt[2] = 0;
	int m = 0;
	b[0] = 0;
	for(int i = 1; i <= n; i++) {
		cnt[a[i]]++;
		if(a[i] == 2) b[m]++;
		else a[++m] = a[i], b[m] = 0;
	}
	n = m;
	for(int i = 1; i <= n; i++) pre[0][i] = pre[0][i - 1], pre[1][i] = pre[1][i - 1], pre[a[i]][i]++;
}

int f[N][N][2][2];

void chkmin(int &x, int y) { if(x > y) x = y;}

int main() {
#ifndef DEBUG
	freopen("phalanx.in", "r", stdin);
	freopen("phalanx.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		preprocess();
		// f[i][0][0][0] = (a[1] == a[2] == ... == a[i] ? 0 : INF)
		// f[i][j][k0][1] <- f[i'][j - 1][k0][k1] + pre[0][i] - pre[0][i'] + [b[i'] = 0]
		// f[i][j][1][k1] <- f[i'][j - 1][k0][k1] + pre[1][i] - pre[1][i'] + [b[i'] = 0]
		// f[i][j][1][1]  <- f[i'][j - 2][k0][k1] + pre[0][i] - pre[0][i'] + max(2 - b[i'], 0)
		// f[i][j][1][1]  <- f[i'][j - 2][k0][k1] + pre[1][i] - pre[1][i'] + max(2 - b[i'], 0)
		for(int i = 0; i <= cnt[2]; i++) mn1[i][0] = mn1[i][1] = mn2[i][0] = mn2[i][1] = mn3[i] = mn4[i] = INF;
		for(int i = 0; i <= n; i++) for(int j = 0; j <= cnt[2]; j++) for(int k0 = 0; k0 <= 1; k0++) for(int k1 = 0; k1 <= 1; k1++) f[i][j][k0][k1] = INF;
		f[0][0][1][1] = 0;
		for(int i = 1; i <= n; i++) {
			if(pre[0][i]) f[i][0][1][0] = pre[1][i];
			if(pre[1][i]) f[i][0][0][1] = pre[0][i];
		}
		for(int i = 0; i <= n; i++) {
			if(i)
				for(int j = 0; j <= cnt[2]; j++) for(int k0 = 0; k0 <= 1; k0++) for(int k1 = 0; k1 <= 1; k1++) {
					if(j >= 1) chkmin(f[i][j][k0][1], mn1[j - 1][k0] + pre[0][i]);
					if(j >= 1) chkmin(f[i][j][1][k1], mn2[j - 1][k1] + pre[1][i]);
					if(j >= 2) chkmin(f[i][j][1][1], mn3[j - 2] + pre[0][i]);
					if(j >= 2) chkmin(f[i][j][1][1], mn4[j - 2] + pre[1][i]);
				}
			for(int j = 0; j <= cnt[2]; j++) for(int k0 = 0; k0 <= 1; k0++) for(int k1 = 0; k1 <= 1; k1++) {
				chkmin(mn1[j][k0], f[i][j][k0][k1] - pre[0][i] + (b[i] == 0));
				chkmin(mn2[j][k1], f[i][j][k0][k1] - pre[1][i] + (b[i] == 0));
				chkmin(mn3[j], f[i][j][k0][k1] - pre[0][i] + std::max(2 - b[i], 0));
				chkmin(mn4[j], f[i][j][k0][k1] - pre[1][i] + std::max(2 - b[i], 0));
			}
		}
		int ans = INF;
		for(int i = 0; i <= cnt[2]; i++) chkmin(ans, f[n][i][1][1]);
		if(!cnt[0]) for(int i = 0; i <= cnt[2]; i++) chkmin(ans, f[n][i][0][1]);
		if(!cnt[1]) for(int i = 0; i <= cnt[2]; i++) chkmin(ans, f[n][i][1][0]);
		if(!cnt[0] && !cnt[1]) for(int i = 0; i <= cnt[2]; i++) chkmin(ans, f[n][i][0][0]);
		for(int i = 0; i <= cnt[2] - 1; i++) for(int k0 = 0; k0 <= 1; k0++) for(int k1 = 0; k1 <= 1; k1++) chkmin(ans, f[n][i][k0][k1] + (b[n] == 0));
		// for(int i = 1; i <= n; i++) printf("pre[%d]: [0]=%d, [1]=%d\n", i, pre[0][i], pre[1][i]);
		// for(int i = 1; i <= n; i++) printf("%d", a[i]), b[i] && printf(" (%d)", b[i]), putchar(' ');
		// puts("");
		// for(int i = 0; i <= n; i++) for(int j = 0; j <= cnt[2]; j++)
		// 	if(f[i][j][0][0] < INF || f[i][j][0][1] < INF || f[i][j][1][0] < INF || f[i][j][1][1] < INF)
		// 		printf("[%d][%d]: [0][0]=%d, [0][1]=%d, [1][0]=%d, [1][1]=%d\n", i, j, f[i][j][0][0], f[i][j][0][1], f[i][j][1][0], f[i][j][1][1]);
		printf("%d\n", ans == INF ? -1 : ans);
	}
	return 0;
} /*
1
10
1 0 2 2 1 0 0 0 0 1
*/