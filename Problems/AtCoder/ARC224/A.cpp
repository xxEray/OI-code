#include <bits/stdc++.h>

typedef long long LL;

bool check(LL x) {
	bool last = false;
	while(x) {
		int t = x % 10;
		if(t == 0) {
			if(last) return true;
			last = true;
		} else last = false;
		x /= 10;
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= 100; i++) if(check((LL)i * n)) {
			printf("%lld\n", (LL)i * n);
			break;
		}
	}
	return 0;
}