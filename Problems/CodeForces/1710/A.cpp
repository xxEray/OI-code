#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
LL n, m;
int K;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%d", &n, &m, &K);
		for(int i = 1; i <= K; i++) scanf("%lld", &a[i]);
		LL cnt = 0;
		bool all_2 = true;
		for(int i = 1; i <= K; i++) {
			LL v = a[i] / m;
			if(v <= 1) continue;
			if(v != 2) all_2 = false;
			cnt += v;
		}
		if(cnt >= n && !(all_2 && n % 2)) { puts("Yes"); continue; }
		cnt = 0;
		all_2 = true;
		for(int i = 1; i <= K; i++) {
			LL v = a[i] / n;
			if(v <= 1) continue;
			if(v != 2) all_2 = false;
			cnt += v;
		}
		if(cnt >= m && !(all_2 && m % 2)) { puts("Yes"); continue; }
		puts("No");
	}
	return 0;
}