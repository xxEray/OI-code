#include <bits/stdc++.h>

int l[300], r[300];

int main() {
	int n = 10;
	for(int i = 1, j = n; i <= 2 * n; i++) {
		while(j && i * i + (j - 1) * (j - 1) >= n * n) j--;
		l[i] = j;
	}
	for(int i = 1, j = 2 * n; i <= 2 * n; i++) {
		while(j && i * i + j * j > 4 * n * n) j--;
		r[i] = j;
	}
	for(int i = 1; i <= n; i++) printf("l[%d] = %d, r[%d] = %d\n", i, l[i], i, r[i]);
	int mx = 0;
	for(int i = 2; i < n; i++) mx = std::max(mx, l[i - 1] - l[i]), mx = std::max(mx, r[i - 1] - r[i]);
	printf("%d\n", mx);
	return 0;
}