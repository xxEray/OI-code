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
		int cnt[100] = {}, t1[100] = {}, t2[100] = {};
		bool flag = true;
		for(int i = 1; i <= n; i++) {
			a[i] -= sum;
			if(a[i] == 0) continue;
			if(__builtin_popcountll(std::abs(a[i])) == 1) {
				int w = 0;
				while(~std::abs(a[i]) >> w & 1) w++;
				if(a[i] > 0) {
					cnt[w + 2]--, cnt[w + 1]++;
					t1[w + 1]++; // [i] -= 2, [i + 1] += 1
				} else {
					cnt[w + 2]++, cnt[w + 1]--;
					t2[w + 1]++; // [i] += 2, [i + 1] -= 1
				}
				continue;
			}
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
		for(int i = 1; i <= 64; i++) {
			if(cnt[i] & 1) { flag = false; break; }
			while(cnt[i] < 0 && t2[i]) cnt[i] += 2, cnt[i + 1] -= 1, t2[i]--;
			while(cnt[i] > 0 && t1[i]) cnt[i] -= 2, cnt[i + 1] += 1, t1[i]--;
			flag &= (cnt[i] == 0);
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}