#include <bits/stdc++.h>

typedef long long LL;

const int N = 50 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K;
int a[N], b[N];
int ca[N], cb[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		int type = 0;
		if(K & 1) {
			K--;
			type = 1;
			int *mna = std::min_element(a + 1, a + n + 1), *mxb = std::max_element(b + 1, b + m + 1);
			if(*mna <= *mxb) std::swap(*mna, *mxb);
			std::swap(n, m);
			for(int i = 1; i <= std::max(n, m); i++) std::swap(a[i], b[i]);
			type = 1;
		}
		while(K) {
			K -= 2;
			for(int i = 1; i <= n; i++) ca[i] = a[i];
			for(int i = 1; i <= m; i++) cb[i] = b[i];
			int *mna = std::min_element(a + 1, a + n + 1), *mxb = std::max_element(b + 1, b + m + 1);
			if(*mna <= *mxb) std::swap(*mna, *mxb);
			int *mxa = std::max_element(a + 1, a + n + 1), *mnb = std::min_element(b + 1, b + m + 1);
			if(*mnb <= *mxa) std::swap(*mnb, *mxa);
			bool flag = false;
			for(int i = 1; i <= n; i++) flag |= (a[i] != ca[i]);
			for(int i = 1; i <= m; i++) flag |= (b[i] != cb[i]);
			if(!flag) break;
		}
		long long ans = 0;
		if(type == 0) for(int i = 1; i <= n; i++) ans += a[i];
		else for(int i = 1; i <= m; i++) ans += b[i];
		printf("%lld\n", ans);
	}
	return 0;
}