#include <cstdio>
#include <algorithm>

typedef long long LL;

LL sum(LL r) {
	if(r <= 2) return 0;
	// printf("sum(%d):\n", r);
	LL ans = 0, i = 2, t = 1;
	while(true) {
		LL ret = 0;
		for(i = 2, t = 1; (i + 1) * 2 <= r; i = (i + 1) * 2, t++)
			ret = (ret + t) * 2;
		ans += ret;
		if(i >= r) break;
		else if(r - i <= 2) { ans += t * (r - i); break; }
		ans += t * 2;
		r -= i + 2;
		i = 2, t = 1;
	}
	return ans;
}

int main() {
	LL l, r;
	scanf("%lld%lld", &l, &r);
	if(l > r) std::swap(l, r);
	printf("%lld\n", sum(r - 1) - sum(l - 1));
	return 0;
}