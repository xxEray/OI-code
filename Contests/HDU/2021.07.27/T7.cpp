#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;

int n, Q;
struct People { int t, c[3]; } a[N];
int lstn[N], sum[N][3];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(lstn, 0, sizeof(lstn));
		memset(sum, 0, sizeof(sum));
		scanf("%d%d", &n, &Q);
		for(int i = 1; i <= n; i++) scanf("%d%2x%2x%2x", &a[i].t, &a[i].c[0], &a[i].c[1], &a[i].c[2]);
		// for(int i = 1; i <= n; i++) printf("%d %d %d %d\n", a[i].t, a[i].c[0], a[i].c[1], a[i].c[2]);
		for(int i = 1; i <= n; i++) {
			if(a[i].t == 1) lstn[i] = i;
			else lstn[i] = lstn[i - 1];
			sum[i][0] = sum[i - 1][0] + a[i].c[0];
			sum[i][1] = sum[i - 1][1] + a[i].c[1];
			sum[i][2] = sum[i - 1][2] + a[i].c[2];
		}
		while(Q--) {
			int l, r;
			scanf("%d%d", &l, &r);
			int last = std::max(lstn[r], l);
			int ans[3] = {0, 0, 0};
			ans[0] = std::min(sum[r][0] - sum[last - 1][0], 255);
			ans[1] = std::min(sum[r][1] - sum[last - 1][1], 255);
			ans[2] = std::min(sum[r][2] - sum[last - 1][2], 255);
			printf("%02X%02X%02X\n", ans[0], ans[1], ans[2]);
		}
	}
	return 0;
}