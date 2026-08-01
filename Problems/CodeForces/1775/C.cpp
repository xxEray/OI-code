#include <cstdio>
#include <algorithm>

typedef long long LL;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL x, y;
		scanf("%lld%lld", &x, &y);
		if(x == y) { printf("%lld\n", x); continue; }
		int i;
		LL v = 0;
		for(i = 63; i >= 0; i--)
			if((x >> i & 1) != (y >> i & 1)) break;
			else v += (x & (1LL << i));
		if(y != v || (v >> (i + 1) & 1)) puts("-1");
		else printf("%lld\n", v + (1LL << (i + 1)));
	}
	return 0;
}