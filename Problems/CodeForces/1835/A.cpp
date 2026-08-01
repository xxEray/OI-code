#include <bits/stdc++.h>

typedef long long LL;

int power10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

int len(int x) {
	int ret = 0;
	while(x) ret++, x /= 10;
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int a, b, c;
		LL K;
		scanf("%d%d%d%lld", &a, &b, &c, &K);
		int i = -1;
		for(i = power10[a - 1]; i < power10[a]; i++) {
			LL l = std::max(power10[b - 1], power10[c - 1] - i);
			LL r = std::min(power10[b] - 1, power10[c] - 1 - i);
			if(l > r) continue;
			// printf("i = %d\n", i);
			if(K > r - l + 1) K -= r - l + 1;
			else break;
			// printf("i = %d, K = %lld\n", i, K);
		}
		if(i == -1 || i == power10[a]) { puts("-1"); continue; }
		int ans1 = i, ans2 = power10[b - 1];
		for(; ans2 < power10[b]; ans2++) {
			if(len(ans1 + ans2) == c) K--;
			if(!K) break;
		}
		if(ans2 == power10[b]) { puts("-1"); continue; }
		if(len(ans1 + ans2) == c) printf("%d + %d = %d\n", ans1, ans2, ans1 + ans2);
		else puts("-1");
	}
	return 0;
} /*
7
1 1 1 9
2 2 3 1
2 2 1 1
1 5 6 42
1 6 6 10000000
5 5 6 3031568815
6 6 6 1000000000000

*/