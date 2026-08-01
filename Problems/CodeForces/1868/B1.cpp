#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		LL sum = 0;
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum += a[i];
		if(sum % n) { puts("No"); continue; }
		sum /= n;
		int cnt[100] = {};
		bool flag = true;
		for(int i = 1; i <= n; i++) {
			a[i] -= sum;
			if(a[i] == 0) continue;
			bool fl = false;
			for(int j = 0; j <= 63; j++) if(__builtin_popcountll(a[i] + (1LL << j)) == 1) {
				fl = true;
				a[i] += (1LL << j);
				int w = 0;
				while(~a[i] >> w & 1) w++;
				cnt[j + 1]++, cnt[w + 1]--;
				break;
			}
			if(!fl) { flag = false; break; }
		}
		for(int i = 1; i <= 64; i++) flag &= (cnt[i] == 0);
		puts(flag ? "Yes" : "No");
	}
	return 0;
}