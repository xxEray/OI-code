#include <bits/stdc++.h>

typedef long long LL;

inline LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

int mp[1000005];

int main() {
	for(int i = 0; i < 100; i++) {
		if(i % 2 == 0 || i % 5 == 0) continue;
		mp[qpow(i, i, 100)] = i;
	}
	int T; scanf("%d", &T);
	while(T--) {
		int x;
		scanf("%d", &x);
		if(!mp[x % 100]) { puts("-1"); continue; }
		int v = mp[x % 100];
		bool flag = false;
		for(int i = 0; i < 10000000; i++) {
			int j = i * 100 + v;
			if(qpow(j, j, 1000000000) == x) { printf("%d\n", j); flag = true; break; }
		}
		if(!flag) puts("-1");
	}
	return 0;
}