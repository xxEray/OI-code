#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N], b[N];
int n, m, K;

bool check(int x) {
	int cnt = 0, tot = 0;
	for(int i = 1; i <= n; i++)
		if(a[i] + tot <= x) tot += a[i];
		else cnt++, tot = a[i];
	if(tot) cnt++;
	return cnt <= K;
}

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
	int ans = 0x3f3f3f3f;
	for(int i = 0; i < m; i++) {
		int sum = 0;
		for(int j = 1; j <= n; j++) a[j] = (b[j] + i) % m, sum += a[j];
		if(!check(ans - 1)) continue;
		int l = *std::max_element(a + 1, a + n + 1), r = ans;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		ans = std::min(ans, l);
	}
	printf("%d\n", ans);
	return 0;
} /*
12 47 8
22 20 36 15 9 4 5 28 13 3 40 31
*/
