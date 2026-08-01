#include <bits/stdc++.h>

typedef long long LL;

const int N = (1 << 18) + 5;

int K;
LL a[N];

int last[N];

int main() {
	srand(time(0));
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &K);
		for(int i = 1; i <= (1 << (K + 1)); i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= (1 << (K + 1)); i++) a[i] ^= a[i - 1];
		std::map<LL, std::pair<int, int>> mp;
		for(int i = 0; i < (1 << K); i++) last[i] = -1;
		for(int i = 0; i <= (1 << (K + 1)); i++) {
			if(last[a[i] >> K] != -1) {
				int l1 = last[a[i] >> K] + 1, r1 = i;
				if(mp.count(a[l1 - 1] ^ a[r1])) {
					auto p = mp[a[l1 - 1] ^ a[r1]];
					int l2 = p.first, r2 = p.second;
					// printf("find [%d, %d] [%d, %d]\n", l1, r1, l2, r2);
					if(l1 > l2) std::swap(l1, l2), std::swap(r1, r2);
					if(r1 < l2) printf("%d %d %d %d\n", l1, r1, l2, r2);
					else printf("%d %d %d %d\n", l1, l2 - 1, std::min(r1, r2) + 1, std::max(r1, r2));
					break;
				} else mp[a[l1 - 1] ^ a[r1]] = {l1, r1};
			}
			last[a[i] >> K] = i;
		}
	}
	return 0;
}