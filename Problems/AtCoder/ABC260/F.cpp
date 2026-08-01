#include <cstdio>
#include <algorithm>
#include <bitset>

const int N = 3e5 + 5;
const int M = 3000 + 5;

int a[N], b[N];
int n, m, K;

std::bitset<M> msk[N], cnt[M];

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= K; i++) { scanf("%d%d", &a[i], &b[i]); b[i] -= n; msk[a[i]][b[i]] = 1; }
	int x = -1;
	for(int i = 1; i <= K; i++) {
		if((cnt[b[i]] & msk[a[i]]).count() > 1) { x = i; break; }
		else cnt[b[i]] |= msk[a[i]];
	}
	if(x == -1) puts("-1");
	else {
		std::bitset<M> tmp = cnt[b[x]] & msk[a[x]];
		int p = b[x];
		tmp[p] = 0;
		int q;
		for(q = 1; q <= m; q++) if(tmp[q]) break;
		int r = 0, c = 0;
		for(int i = 1; i <= n; i++) if(msk[i][p] && msk[i][q]) {
			if(!r) r = i;
			else {
				c = i;
				break;
			}
		}
		printf("%d %d %d %d\n", r, c, p + n, q + n);
	}
	return 0;
}