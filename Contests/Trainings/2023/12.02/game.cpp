#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n, K;
LL a[N], b[N];

LL ans;
bool check(LL x) {
	std::priority_queue<std::pair<LL, int>, std::vector<std::pair<LL, int>>, std::greater<>> q;
	LL sum = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		q.emplace(a[i], 1);
		if(q.top().first + b[i] - x < 0) {
			cnt += q.top().second;
			sum += q.top().first + b[i] - x;
			q.pop();
			q.emplace(-(b[i] - x), 0);
		}
	}
	ans = sum;
	return cnt < K;
}

int main() {
	scanf("%d%d", &n, &K);
	if(K > n) { puts("1000000000000000000"); return 0; }
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	LL l = -2e9, r = 2e9;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	l--;
	check(l);
	printf("%lld\n", ans + l * K);
	return 0;
}