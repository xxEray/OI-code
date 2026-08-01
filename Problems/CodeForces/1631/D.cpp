#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 2e5 + 5;

int a[N], b[N], sum[N];
int n, m;

bool check(int len) {
	int l = 1;
	for(int i = 1; i + len - 1 <= n; i++) if(sum[i + len - 1] - sum[i - 1] > sum[l + len - 1] - sum[l - 1]) l = i;
	int r = l + len - 1;
	// printf("check(%d): [%d, %d]\n", len, l, r);
	for(int i = 1; i <= n; i++) b[i] = (l <= a[i] && a[i] <= r ? 1 : -1);
	int most = 1, cnt = 0;
	for(int i = 1; i <= n; i++) {
		cnt += b[i];
		if(cnt == 1 && most < m) most++, cnt = 0;
	}
	return most >= m && cnt >= 1;
}
void getans(int len) {
	int l = 1;
	for(int i = 1; i + len - 1 <= n; i++) if(sum[i + len - 1] - sum[i - 1] > sum[l + len - 1] - sum[l - 1]) l = i;
	int r = l + len - 1;
	printf("%d %d\n", l, r);
	for(int i = 1; i <= n; i++) b[i] = (l <= a[i] && a[i] <= r ? 1 : -1);
	std::vector<int> ans = {0};
	int most = 1, cnt = 0;
	for(int i = 1; i <= n; i++) {
		cnt += b[i];
		if(cnt == 1 && most < m) ans.push_back(i), most++, cnt = 0;
	}
	// printf("vct: "); for(int x : ans) { printf("%d ", x); } puts("");
	assert((int)ans.size() >= m && cnt >= 1);
	for(int i = 1; i <= m - 1; i++) printf("%d %d\n", ans[i - 1] + 1, ans[i]);
	printf("%d %d\n", ans[m - 1] + 1, n);
}

int main() {
	// freopen("out.txt", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) sum[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[a[i]]++;
		for(int i = 1; i <= n; i++) sum[i] += sum[i - 1];
		int l = 1, r = n;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		getans(l);
	}
	return 0;
} /*
3
2 1
1 2
4 2
1 2 2 2
11 3
5 5 5 1 5 5 1 5 5 5 1

111110000
*/