#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 1e5 + 5;
const int MX = 1e5;
const int INF = 0x3f3f3f3f;

int a[N];
int n, K;

std::vector<int> cnt[N];
int tot[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 0; i <= MX; i++) cnt[i].clear(), cnt[i].shrink_to_fit();
		for(int i = 1; i <= n; i++) tot[i] = 1;
		int l = INF, r = MX;
		for(int i = 1; i <= n; i++) l = std::min(l, a[i]), cnt[a[i]].push_back(i);
		int ans = INF, flag = true;
		while(r >= 0 && flag) {
			ans = std::min(ans, r - l);
			for(int i : cnt[r]) {
				if(a[i] / tot[i] == 0 || a[i] / (a[i] / tot[i]) + 1 > K) { flag = false; break; }
				tot[i] = a[i] / (a[i] / tot[i]) + 1;
				cnt[a[i] / tot[i]].push_back(i);
				l = std::min(l, a[i] / tot[i]);
			}
			cnt[r].clear(), cnt[r].shrink_to_fit();
			r--;
		}
		printf("%d\n", ans);
	}
	return 0;
}