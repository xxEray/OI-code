#include <cstdio>

typedef long long LL;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		LL a, b, n;
		scanf("%lld%lld%lld", &n, &a, &b);
		if(a == 1) { puts((n - 1) % b == 0 ? "Yes" : "No"); continue; }
		LL power = 1;
		bool flag = false;
		for(int i = 0; power <= n; i++) {
			if((n - power) % b == 0) { flag = true; break; }
			power *= a;
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}