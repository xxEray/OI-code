#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, K;
int a[N], pos[N];

std::vector<int> seq;

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]] = i;
	LL sum = 0;
	for(int i = n; i >= n - K + 1; i--) seq.push_back(pos[i]), sum += i;
	std::sort(seq.begin(), seq.end());
	LL ans = 1;
	for(int i = 0; i < (int)seq.size() - 1; i++) (ans *= seq[i + 1] - seq[i]) %= MOD;
	printf("%lld %lld\n", sum, ans);
	return 0;
}