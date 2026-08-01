#include <cstdio>
#include <algorithm>

int calc(int x) {
	int mx = 0, mn = 9;
	while(x) mx = std::max(mx, x % 10), mn = std::min(mn, x % 10), x /= 10;
	return mx - mn;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int ans = 0, ansid = l;
		for(int i = l; i <= r && ans < 9; i++)
			if(ans < calc(i)) ansid = i, ans = calc(i);
		printf("%d\n", ansid);
	}
	return 0;
}