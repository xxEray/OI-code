#include <cstdio>
#include <algorithm>
#include <set>

const int N = 1000 + 5;

int n, m;

int p[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) p[i] = m;
	for(int T = 1; T <= m; T++) {
		char s[2]; int x;
		scanf("%s%d", s, &x);
		if(s[0] == 'L') {
			for(int i = 1; i < x; i++) if(p[i] > 1) p[i]--;
			p[x] = 1;
		} else if(s[0] == 'R') {
			for(int i = n; i > x; i--) if(p[i] > 1) p[i]--;
			p[x] = 1;
		}
	}
	long long ans = 1;
	for(int i = 1; i <= n; i++) (ans *= p[i]) %= 998244353;
	printf("%lld\n", ans);
	return 0;
}