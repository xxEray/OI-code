#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e7 + 5;
const int INF = 0x3f3f3f3f;

bool isprm[N];
int prm[N], cprm;

bool isprime(int x) { return x > 0 && isprm[x]; }

int main() {
	for(int i = 2; i <= 20000005; i++) isprm[i] = true;
	for(int i = 2; i <= 20000005; i++) if(isprm[i]) {
		prm[++cprm] = i;
		for(int j = i + i; j <= 20000005; j += i) isprm[j] = false;
	}
	int T;
	scanf("%d", &T);
	while(T--) {
		int x;
		scanf("%d", &x);
		if(isprime(x)) { puts("1"); continue; }
		if(isprime(2 * x + 1) || isprime(2 * x - 1)) { puts("2"); continue; }
		int ans = INF;
		int l = 1, r = cprm;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(1 - prm[mid] <= x && x <= prm[mid]) r = mid;
			else l = mid + 1;
		}
		ans = std::min(ans, 2 * prm[l]);
		l = 1, r = cprm;
		while(l < r) {
			int mid = (l + r) >> 1;
			if((2 - (prm[mid] + 1) / 2) <= x && x <= (prm[mid] + 1) / 2) r = mid;
			else l = mid + 1;
		}
		ans = std::min(ans, prm[l]);
		printf("%d\n", ans);
	}
	return 0;
}