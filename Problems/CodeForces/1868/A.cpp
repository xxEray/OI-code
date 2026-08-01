#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, m;

std::vector<int> a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		if(m == 1) {
			puts("0");
			for(int i = 1; i <= n; i++) puts("0");
			continue;
		}
		for(int i = 1; i <= n; i++) a[i].clear(), a[i].shrink_to_fit(), a[i].resize(m + 1);
		int K = std::min(n + 1, m);
		for(int i = 1; i <= K - 1; i++) for(int j = 1; j <= K; j++) a[i][j] = (i + j - 1) % K;
		for(int i = 1; i <= K - 1; i++) for(int j = K + 1; j <= m; j++) a[i][j] = j - 1;
		for(int i = K; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = a[1][j];
		printf("%d\n", K);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) printf("%d ", a[i][j]);
			puts("");
		}
	}
	return 0;
}