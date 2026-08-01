#include <bits/stdc++.h>

typedef long long LL;

int n, m;
bool check(int x) {
	LL val = 1;
	LL cnt = n;
	LL cnt2 = 0;
	for(int i = 0; i <= x && cnt2 <= (LL)x * m; i++) {
		if(i) val = val * (x - i + 1) / i;
		if(cnt2 + val * i <= (LL)x * m) cnt -= val, cnt2 += val * i;
		else cnt -= ((LL)x * m - cnt2) / i, cnt2 = (LL)x * m + 1;
		if(cnt <= 0) return true;
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		int l = 0, r = 1e9;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
	return 0;
} /*
10
1 1
2 1
2 2
3 1
3 2
3 3
37 6
1000000000 1
1000000000 1000000000
1000000000 100000000
*/