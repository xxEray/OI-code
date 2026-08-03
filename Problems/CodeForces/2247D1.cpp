#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n, Q;
int a[N];

int mn[21][N], mx[21][N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &Q);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]), mn[0][i] = mx[0][i] = a[i];
		if(std::is_sorted(a, a + n)) { puts("0"); continue; }
		for(int j = 1; j <= 20; j++) {
			bool flag = true;
			for(int i = 0; i < n; i += (1 << j)) {
				if(i + (1 << (j - 1)) < n) {
					mn[j][i] = std::min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
					mx[j][i] = std::max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
				} else {
					mn[j][i] = mn[j - 1][i], mx[j][i] = mx[j - 1][i];
				}
				// printf("[%d][%d]: mn=%d, mx=%d\n", j, i, mn[j][i], mx[j][i]);
			}
			for(int i = 0; i + (1 << j) < n; i += (1 << j))
				flag &= (mx[j][i] <= mn[j][i + (1 << j)]);
			if(flag) { printf("%d\n", (1 << (j - 1))); break; }
		}
	}
	return 0;
} /*
1
7 0
1 1 1 1 2 2 1
*/