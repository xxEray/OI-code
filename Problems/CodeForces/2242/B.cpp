#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int cnt[4] = {};
		for(int i = 1; i <= n; i++) cnt[a[i]]++;
		bool flag = false;
		int now[4] = {}, mn = INF, sum = 0;
		for(int i = n; i >= 2; i--) {
			if(a[i] == 3) sum--;
			else sum++;
			now[a[i]]++;
			flag |= (sum >= mn && cnt[2] + cnt[3] - now[2] - now[3] <= (i - 1) / 2);
			mn = std::min(mn, sum);
			// printf("i = %d: %d\n", i, (int)flag);
		}
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
}