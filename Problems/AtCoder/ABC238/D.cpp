#include <cstdio>
#include <algorithm>

typedef long long LL;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		LL a, s;
		scanf("%lld%lld", &a, &s);
		if(a * 2 > s) { puts("No"); continue; }
		s -= 2 * a;
		puts((a & s) ? "No" : "Yes");
	}
	return 0;
}