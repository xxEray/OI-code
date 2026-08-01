#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N];

bool f[N];
bool check(int x) {
	for(int i = 1; i <= n; i++) f[i] = false;
	int cnt = 0;
	for(int i = 1, j = 0; i < n; i++) {
		f[i] |= (i > 1 && a[i + 1] - a[1] <= 2 * x);
		while(j <= i - 2 && a[i + 1] - a[j] > 2 * x) cnt -= f[j], j++;
		f[i] |= cnt;
		cnt += f[i - 1];
	}
	for(int i = 1; i <= n; i++) if(a[n] - a[i] <= 2 * x && f[i]) return true;
	return false;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if(n == 2) { printf("%d\n", (a[2] - a[1]) / 2); return 0; }
	int l = 0, r = 1e9;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}