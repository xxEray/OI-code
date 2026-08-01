#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
LL m;
LL a[N];

bool tin[N];

int main() {
	scanf("%d%lld%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	if(K == 1) {
		for(int i = 1; i <= n; i++) if(a[i] <= 1000000) tin[a[i]] = true;
		bool flag = false;
		for(int i = 0; i <= std::min(m, 1000000LL); i++) if(!tin[i]) { printf("1 %d\n", i); flag = true; break; }
		if(!flag) puts("0 0");
		return 0;
	}
	K--;
	if(K >= n) {
		printf("%lld 0\n", m + 1);
		return 0;
	}
	LL ansid = 0, ans = -1;
	a[0] = 0, a[n + 1] = m;
	for(int i = 0; i <= n + 1; i++) {
		LL ret = (i + K < n + 1 && (i == 0 || a[i] > a[i - 1]) ? ((a[i + K] - 1) + a[i]) / 2 : m) - (i - K > 0 && (i == n + 1 || a[i] < a[i + 1]) ? (a[i] + (a[i - K] + 1) + 1) / 2 : 0) + 1;
		if(ret > ans || (ret == ans && ansid > a[i])) ansid = a[i], ans = ret;
	}
	for(int i = 0; i <= n; i++) {
		if(a[i] + 1 < a[i + 1]) {
			LL ret = (i + K + 1 < n + 1 ? ((a[i + K + 1] - 1) + (a[i] + 1)) / 2 : m) - (i - K > 0 ? ((a[i] + 1) + (a[i - K] + 1) + 1) / 2 : 0) + 1;
			if(ret > ans || (ret == ans && ansid > a[i] + 11)) ansid = a[i] + 1, ans = ret;
		}
		if(a[i] + 2 < a[i + 1]) {
			LL ret = (i + K + 1 < n + 1 ? ((a[i + K + 1] - 1) + (a[i] + 2)) / 2 : m) - (i - K > 0 ? ((a[i] + 2) + (a[i - K] + 1) + 1) / 2 : 0) + 1;
			if(ret > ans || (ret == ans && ansid > a[i] + 2)) ansid = a[i] + 2, ans = ret;
		}
	}
	for(int i = 1; i <= n + 1; i++) {
		if(a[i] - 1 > a[i - 1]) {
			LL ret = (i + K < n + 1 ? ((a[i + K] - 1) + (a[i] - 1)) / 2 : m) - (i - K - 1 > 0 ? ((a[i] - 1) + (a[i - K - 1] + 1) + 1) / 2 : 0) + 1;
			if(ret > ans || (ret == ans && ansid > a[i] - 1)) ansid = a[i] - 1, ans = ret;
		}
		if(a[i] - 2 > a[i - 1]) {
			LL ret = (i + K < n + 1 ? ((a[i + K] - 1) + (a[i] - 2)) / 2 : m) - (i - K - 1 > 0 ? ((a[i] - 2) + (a[i - K - 1] + 1) + 1) / 2 : 0) + 1;
			if(ret > ans || (ret == ans && ansid > a[i] - 2)) ansid = a[i] - 2, ans = ret;
		}
	}
	printf("%lld %lld\n", ans, ansid);
	return 0;
}