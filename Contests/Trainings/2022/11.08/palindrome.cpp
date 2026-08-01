#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 3e5 + 5;

int n, Q;
char t[N], s[N << 1];

int val[N << 1];
int m = 0;
void manacher() {
	s[++m] = '#';
	for(int i = 1; i <= n; i++) s[++m] = t[i], s[++m] = '#';
	int r = 0, mid = 0;
	for(int i = 1; i <= m; i++) {
		if(r >= i) val[i] = std::min(r - i, val[2 * mid - i]);
		while(i - val[i] - 1 >= 1 && i + val[i] + 1 <= m && s[i + val[i] + 1] == s[i - val[i] - 1]) val[i]++;
	}
}

struct ST_Table {
	int lg[N << 1], gomx[N << 1][21];
	void init() {
		lg[0] = -1;
		for(int i = 1; i <= m; i++) lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i <= m; i++) gomx[i][0] = val[i] + 1;
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= m; i++)
				gomx[i][j] = std::max(gomx[i][j - 1], gomx[i + (1 << (j - 1))][j - 1]);
	}
	int max(int l, int r) {
		if(l > r) return 0;
		int k = lg[r - l + 1];
		return std::max(gomx[l][k], gomx[r - (1 << k) + 1][k]);
	}
} ST;

int main() {
#ifndef DEBUG
	freopen("palindrom.in", "r", stdin);
	freopen("palindrom.out", "w", stdout);
#endif
	scanf("%s", t + 1);
	n = strlen(t + 1);
	manacher();
	ST.init();
	scanf("%d", &Q);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		l = l * 2 + 1, r = r * 2 + 3;
		int left = 1, right = r - l + 2;
		while(left < right) {
			int mid = (left + right) >> 1;
			if(ST.max(l + mid - 1, r - mid + 1) >= mid) left = mid + 1;
			else right = mid;
		}
		left--;
		printf("%d\n", left - 1);
	}
	return 0;
}