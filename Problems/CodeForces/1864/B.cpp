#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, K;
char a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%s", &n, &K, a + 1);
		std::vector<int> vct[2];
		for(int i = 1; i <= n; i++) vct[i & 1].push_back(a[i]);
		std::sort(vct[0].begin(), vct[0].end()), std::sort(vct[1].begin(), vct[1].end());
		if(K & 1) {
			for(int i = 1, j = 0; i <= n; i += 2) b[i] = vct[1][j++];
			for(int i = 2, j = 0; i <= n; i += 2) b[i] = vct[0][j++];
		} else if(n == K) {
			if(vct[1] > vct[0]) std::swap(vct[0], vct[1]);
			for(int i = 1, j = 0; i <= n; i += 2) b[i] = vct[1][j++];
			for(int i = 2, j = 0; i <= n; i += 2) b[i] = vct[0][j++];
		} else {
			std::sort(a + 1, a + n + 1);
			for(int i = 1; i <= n; i++) b[i] = a[i];
		}
		for(int i = 1; i <= n; i++) putchar(b[i]);
		puts("");
	}
	return 0;
}