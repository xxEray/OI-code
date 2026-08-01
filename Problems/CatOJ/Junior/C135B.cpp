#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 5e5 + 5;

int n;
int a[2 * N];

std::vector<int> b[2 * N];

int pre[2 * N], suf[2 * N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[2 * i - 1]), a[2 * i - 1] = a[2 * i - 1] * 2 - 1;
	for(int i = 1; i <= 2 * n; i += 2) b[(i + a[i]) / 2].push_back(std::abs(i - (i + a[i]) / 2));
	for(int i = 1; i <= 2 * n; i++) pre[i] = pre[i - 1] + (a[i] && a[i] == i);
	for(int i = 2 * n; i >= 1; i--) suf[i] = suf[i + 1] + (a[i] && a[i] == i);
	int ans = 0;
	for(int i = 1; i <= 2 * n; i++) {
		std::sort(b[i].begin(), b[i].end());
		int tot = 0;
		for(int j : b[i]) tot++, ans = std::max(ans, pre[i - j - 1] + suf[i + j + 1] + tot);
	}
	printf("%d\n", ans);
	return 0;
}