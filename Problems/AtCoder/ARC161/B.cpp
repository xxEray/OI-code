#include <bits/stdc++.h>

typedef long long LL;

LL n;
int a[100];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%lld", &n);
		for(int i = 63; i >= 0; i--) a[i] = n >> i & 1;
		int cnt = 0;
		for(int i = 0; i <= 63; i++) cnt += a[i];
		bool flag = true;
		if(cnt >= 3) {
			int cnt2 = 0;
			for(int i = 63; i >= 0; i--) {
				cnt2 += a[i];
				if(cnt2 > 3) a[i] = 0;
			}
		} else if(cnt == 2) {
			int x = -1, y = -1;
			for(int i = 63; i >= 0; i--) if(a[i]) (x == -1 ? x : y) = i;
			if(y >= 2) a[y] = 0, a[y - 1] = a[y - 2] = 1;
			else a[y] = 0, cnt = 1;
		}
		if(cnt == 1) {
			for(int i = 63; i >= 0; i--) if(a[i]) {
				if(i < 3) flag = false;
				else a[i] = 0, a[i - 1] = a[i - 2] = a[i - 3] = 1;
				break;
			}
		}
		n = 0;
		for(int i = 0; i <= 63; i++) n |= ((LL)a[i] << i);
		printf("%lld\n", flag ? n : -1LL);
	}
	return 0;
}