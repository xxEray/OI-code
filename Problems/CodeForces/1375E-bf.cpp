#include <bits/stdc++.h>

const int N = 1e3 + 5;

int n;
int a[N], b[N];

std::pair<int, int> d[N * N];
int p[N * N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int c = 0;
	for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) if(a[i] > a[j]) d[++c] = {i, j};
	for(int i = 1; i <= c; i++) p[i] = i;
	do {
		for(int i = 1; i <= n; i++) b[i] = a[i];
		for(int i = 1; i <= c; i++) std::swap(b[d[p[i]].first], b[d[p[i]].second]);
		if(std::is_sorted(b + 1, b + n + 1)) {
			printf("%d\n", c);
			for(int i = 1; i <= c; i++) printf("%d %d\n", d[p[i]].first, d[p[i]].second);
			break;
		}
	} while(std::next_permutation(p + 1, p + c + 1));
	return 0;
}