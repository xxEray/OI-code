#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;

int n, x;
LL cnt[N];

int main() {
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; i++) { int y; scanf("%d", &y); cnt[y]++; }
	for(int i = 1; i <= 1000000; i++) cnt[i + 1] += cnt[i] / (i + 1), cnt[i] %= i + 1;
	bool flag = true;
	for(int i = 1; i < x; i++) flag &= cnt[i] == 0;
	puts(flag ? "Yes" : "No");
	return 0;
}