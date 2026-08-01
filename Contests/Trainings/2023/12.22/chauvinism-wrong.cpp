#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
LL a[N], b[N];

bool check(LL x) {
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += (a[i] - x <= b[i]);
	// printf("check(%lld) = %d (cnt=%d)\n", x, cnt < K, cnt);
	return cnt < K;
}

LL c[N];
char out[N];
void get_answer(LL x) {
	int cc = 0;
	for(int i = 1; i <= n; i++) c[i] = std::min(a[i] - x, b[i]), cc += (a[i] - x <= b[i]);
	LL sum = 0, mn = LLINF, ret = 0;
	for(int i = 0; i <= n; i++) {
		sum += c[i];
		mn = std::min(mn, sum);
		ret = std::max(ret, sum - mn);
	}
	printf("x = %lld\n", x);
	printf("%lld\n", ret + cc * x - K * x);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(a[i] - x < b[i]) out[i] = 'A', cnt++;
		else out[i] = 'B';
	for(int i = 1; i <= n && cnt < K; i++) if(a[i] - x == b[i]) out[i] = 'A', cnt++;
	out[n + 1] = 0;
	puts(out + 1);
}

int main() {
#ifndef DEBUG
	freopen("chauvinism.in", "r", stdin);
	freopen("chauvinism.out", "w", stdout);
#endif
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	LL l = -2.01e14, r = 2.01e14;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	get_answer(l);
	return 0;
} /*
6 2
-1 7 0 2 -5 0
3 1 4 -3 -3 12

0: 14
1: 8
2: 4
3: 1
4: 1
5: 3
6: 9
*/