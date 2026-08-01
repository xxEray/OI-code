#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;
LL a[N];

LL L, R;

bool check(LL x) {
	for(int i = 1, j = 0; i <= n; i++) {
		LL k = std::max(L - a[i], 0LL);
		if(k > x) continue;
		while(j < n && a[j + 1] <= R + (x - k)) j++;
		if(j - i + 1 >= m) return /* printf("check(%d) = 1\n", x),  */true;
	}
	return /* printf("check(%d) = 0\n", x),  */false;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	L = a[1], R = a[2];
	for(int i = 3; i <= n; i++) a[i - 2] = a[i];
	n -= 2;
	std::sort(a + 1, a + n + 1);
	LL l = 0, r = 2000000000;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
}