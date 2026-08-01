#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];

std::map<std::array<int, 3>, LL> mp;
LL solve(int l, int r, int h) {
	if(l > r) return 0;
	if(mp.count({l, r, h})) return mp[{l, r, h}];
//	printf("solve(%d, %d, %d)\n", l, r, h);
	int mn = INF, mx = 0;
	for(int i = l; i <= r; i++) mn = std::min(mn, a[i] - h), mx = std::max(mx, a[i] - h);
	LL ret1 = LLINF, ret2 = LLINF;
	ret1 = (LL)(mx + mx - mn + 1) * mn / 2;
	for(int i = l; i <= r; ) {
		while(i <= r && a[i] - h == mn) i++;
		if(i > r) break;
		int j = i;
		while(j < r && a[j + 1] - h > mn) j++;
		ret1 += solve(i, j, h + mn);
		i = j + 1;
	}
	ret2 = 0;
	for(int i = l; i <= r; ) {
		while(i <= r && a[i] - h == mx) ret2 += a[i] - h, i++;
		if(i > r) break;
		int j = i;
		while(j < r && a[j + 1] - h < mx) j++;
		ret2 += solve(i, j, h);
		i = j + 1;
	}
	return mp[{l, r, h}] = std::min(ret1, ret2);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	printf("%lld\n", solve(1, n, 0));
	return 0;
}