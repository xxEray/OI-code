#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, K;
int a[N], b[N];

std::vector<int> pos[2 * N];
int seq[N], out[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= 2 * n; i++) pos[i].clear();
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]].push_back(i);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
		int mn = 0, mx = 0;
		for(int i = 1, j = 1; i <= n; i++) {
			while(j <= n && a[i] > b[j]) j++;
			if(j > n) { mn = n - i + 1; break; }
			j++;
		}
		for(int j = 1, i = 1; j <= n; j++) {
			while(i <= n && a[i] <= b[j]) i++;
			if(i > n) break;
			mx++, i++;
		}
		if(K < mn || K > mx) { puts("NO"); continue; }
		puts("YES");
		int c = 0;
		for(int i = K + 1; i <= n; i++) seq[++c] = b[i];
		for(int i = 1; i <= K; i++) seq[++c] = b[i];
		for(int i = 1; i <= n; i++) {
			out[pos[a[i]].back()] = seq[i];
			pos[a[i]].pop_back();
		}
		for(int i = 1; i <= n; i++) printf("%d ", out[i]);
		puts("");
	}
	return 0;
} /*
1
5 3
3 3 5 5 7
2 4 6 6 8
*/