#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int a[N];

int calc(int ca, int cb) {
	if(ca == 0 && cb == 1) return 0;
	int v = cb / 3;
	if(cb % 3 == 1) v++;
	return v;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int cnta = 0, cntb = 0;
		long long sum = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i] & 1) cntb++;
			else cnta++;
			sum += a[i];
			printf("%lld ", sum - calc(cnta, cntb));
		}
		puts("");
	}
	return 0;
}