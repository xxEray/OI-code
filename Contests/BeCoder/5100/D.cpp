#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n; LL K;
int p[N], q[N];

struct BIT {
	LL t[N];
	void clear() { for(int i = 1; i <= n; i++) t[i] = 0; }
	void add(int x, LL v) { while(x <= n) t[x] += v, x += x & -x; }
	LL query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
} bit;

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &q[i]), p[q[i]] = i;
		bit.clear();
		for(int i = 1; i <= n; i++) {
			K -= bit.query(p[i] + 1, n);
			bit.add(p[i], 1);
		}
		if(K < 0 || (K & 1)) { puts("NO"); continue; }
		K >>= 1;
		bool flag = false;
		bit.clear();
		for(int i = 1; i <= n; i++) {
			LL val = bit.query(p[i] - 1);
			if(K <= val) {
				// printf("i = %d\n", i);
				int cn = i;
				for(int j = 1; j < i; j++) {
					q[j] = cn--;
					if(K && p[j] < p[i]) {
						K--;
						if(!K) q[i] = cn--;
					}
				}
				if(!val) q[i] = i;
				for(int j = i + 1; j <= n; j++) q[j] = j;
				flag = true;
				break;
			}
			K -= val;
			bit.add(p[i], 1);
		}
		if(flag) {
			puts("YES");
			for(int i = 1; i <= n; i++) printf("%d ", q[i]);
			puts("");
		} else puts("NO");
	}
	return 0;
}