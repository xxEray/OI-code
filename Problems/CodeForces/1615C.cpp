#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N], b[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%1d", &b[i]);
		int cnt[2][2] = {};
		for(int i = 1; i <= n; i++) cnt[a[i]][b[i]]++;
		int ret = n + 1;
		// if((same & 1) == 1) ret = std::min(ret, same);
		// if((diff & 1) == 0) ret = std::min(ret, diff);
		if(cnt[1][1] == cnt[0][0] + 1) ret = std::min(ret, cnt[0][0] + cnt[1][1]);
		if(cnt[1][0] == cnt[0][1]) ret = std::min(ret, cnt[1][0] + cnt[0][1]);
		printf("%d\n", ret == n + 1 ? -1 : ret);
	}
	return 0;
}