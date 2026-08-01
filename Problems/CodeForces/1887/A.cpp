#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N], b[N];

int st;
bool check(int x) {
	for(int i = 1; i <= n - x; i++) {
		int v = (a[i] < st ? a[i] : (a[i - 1] < st ? st : a[i - 1]));
		if(v >= b[i + x]) return false;
	}
	return true;
}

int calc(int x) {
	st = x;
	int l = 0, r = n;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i < n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		std::sort(a + 1, a + n), std::sort(b + 1, b + n + 1);
		a[n] = INF;
		int lans = calc(1);
		int l = 1, r = m + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(calc(mid) == lans) l = mid + 1;
			else r = mid;
		}
		printf("%lld\n", (long long)lans * (l - 1) + (long long)(lans + 1) * (m - l + 1));
	}
	return 0;
}