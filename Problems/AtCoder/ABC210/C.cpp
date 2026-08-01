#include <cstdio>
#include <algorithm>
#include <map>

const int N = 3e5 + 5;

int a[N];
int n, m;

std::map<int, int> cnt;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		cnt[a[i]]++;
		if(i > m) {
			cnt[a[i - m]]--;
			if(cnt[a[i - m]] == 0) cnt.erase(a[i - m]);
		}
		ans = std::max(ans, (int)cnt.size());
	}
	printf("%d\n", ans);
	return 0;
}