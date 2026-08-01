#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
std::pair<int, int> a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x > y) std::swap(x, y);
		a[i] = {x, y};
	}
	LL ans = LLINF;
	std::sort(a + 1, a + n + 1);
	int mx = 0;
	for(int i = 2; i <= n; i++) mx = std::max(mx, a[i].second);
	if(a[1].second <= mx) {
		
	}
	return 0;
}