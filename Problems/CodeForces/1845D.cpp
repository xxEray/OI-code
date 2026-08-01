#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n;
LL a[N];

LL pre[N], suf[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		pre[0] = suf[n + 1] = 0;
		for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
		for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[i];
		for(int i = n; i >= 1; i--) suf[i] = std::max(suf[i], suf[i + 1]);
		LL ans = 0, ansid = 0;
		for(int i = 0; i <= n; i++) if(ans < pre[i] + suf[i + 1]) ans = pre[i] + suf[i + 1], ansid = pre[i];
		printf("%lld\n", ansid);
	}
	return 0;
}