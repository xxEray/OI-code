#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
int a[N];

struct ST_Table {
	int go[21][N], lg[N];
	void init() {
		lg[0] = -1;
		for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1, go[0][i] = i + a[i];
		for(int j = 1; j <= 20; j++) for(int i = 1; i + (1 << j) - 1 <= n; i++)
			go[j][i] = std::max(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int max(int l, int r) {
		if(l > r) return 0;
		int k = lg[r - l + 1];
		return std::max(go[k][l], go[k][r - (1 << k) + 1]);
	}
} ST;

int f[N];
int last[N][2], out[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		ST.init();
		for(int i = 0; i <= n; i++) f[i] = 0, last[i][0] = last[i][1] = 0;
		for(int i = 1; i <= n; i++) {
			int j = std::lower_bound(f, f + i, i - a[i] - 1) - f;
			if(j < i) f[i] = std::max({f[j], i - 1, ST.max(j + 1, i - 1)}), last[i][0] = j, last[i][1] = i;
			if(f[i - 1] >= i && f[i] < std::max(f[i - 1], i + a[i]))
				f[i] = std::max(f[i - 1], i + a[i]), last[i][0] = i - 1, last[i][1] = 0;
			f[i] = std::max(f[i], f[i - 1]);
		}
		if(f[n] >= n) {
			puts("YES");
			for(int i = 1; i <= n; i++) out[i] = 1;
			for(int i = n; i; i = last[i][0]) out[last[i][1]] = 0;
			for(int i = 1; i <= n; i++) putchar(out[i] ? 'R' : 'L');
			puts("");
		} else {
			puts("NO");
		}
	}
	return 0;
} /*
1
8
1 0 2 0 2 1 1 2
*/