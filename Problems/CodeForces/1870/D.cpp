#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n, K;
int a[N];

int c[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		scanf("%d", &K);
		std::vector<int> q;
		for(int i = 1; i <= n; i++) {
			while(!q.empty() && a[q.back()] >= a[i]) q.pop_back();
			q.push_back(i);
		}
		for(int i = 0; i <= n + 1; i++) c[i] = 0;
		int j = 0, lastv = K;
		for(int i : q) {
			int v = K / (a[i] - a[j]);
			v = std::min(v, lastv);
			lastv = v;
			c[j + 1] += v, c[i + 1] -= v;
			K -= v * (a[i] - a[j]);
			j = i;
		}
		for(int i = 1; i <= n; i++) c[i] += c[i - 1];
		for(int i = 1; i <= n; i++) printf("%d ", c[i]);
		puts("");
	}
	return 0;
}