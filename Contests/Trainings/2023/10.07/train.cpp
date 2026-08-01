#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n;
char s[N];

int pre[2][N];
LL pres[2][N];
std::vector<int> pos[2];

int main() {
#ifndef DEBUG
	freopen("train.in", "r", stdin);
	freopen("train.out", "w", stdout);
#endif
	scanf("%d%s", &n, s + 1);
	for(int i = 1; i <= n; i++) s[i] = (s[i] == 'L' ? 0 : 1);
	pos[0].push_back(0), pos[1].push_back(0);
	for(int i = 1; i <= n; i++) {
		pre[0][i] = pre[0][i - 1] + (s[i] == 0);
		pre[1][i] = pre[1][i - 1] + (s[i] == 1);
		pres[0][i] = pres[0][i - 1] + (s[i] == 0) * i;
		pres[1][i] = pres[1][i - 1] + (s[i] == 1) * i;
		pos[s[i]].push_back(i);
	}
	for(int i = 1; i <= n; i++) {
		int cntl = pre[1][i - 1], cntr = pre[0][n] - pre[0][i];
		int cnt, cl, cr;
		LL sum = 0;
		if(s[i] == 0) {
			cnt = std::min(cntl - 1, cntr);
			if(cntl - 1 < cntr) sum += i, cl = cnt + 1, cr = cnt + 1;
			else sum += i + (n + 1), cl = cnt + 1, cr = cnt;
		} else {
			cnt = std::min(cntl, cntr - 1);
			if(cntr - 1 < cntl) sum += -i + (n + 1), cl = cnt + 1, cr = cnt + 1;
			else sum -= i, cl = cnt, cr = cnt + 1;
		}
		sum += 2 * (pres[0][pos[0][pre[0][i] + cr]] - pres[0][i]) - 2 * (pres[1][i - 1] - pres[1][pos[1][pre[1][i - 1] - cl]]);
//		printf("cl = %d, cr = %d, sum = %lld\n", cl, cr, sum);
		printf("%lld ", sum);
	}
	puts("");
	return 0;
}
