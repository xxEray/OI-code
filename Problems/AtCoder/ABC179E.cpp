#include <cstdio>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;

int vis[N];
std::vector<LL> nums;

LL n, x, m;

int main() {
	std::scanf("%lld%lld%lld", &n, &x, &m);
	int st;
	for(int i = 0; !(st = vis[x]); i++) {
		vis[x] = i;
		nums.push_back(x);
		x = x * x % m;
	}
	LL sum = 0;
	for(int i = st; i < (int)nums.size(); i++) sum += nums[i];
	n -= st;
	sum *= n / ((int)nums.size() - st);
	n %= (int)nums.size() - st;
	for(int i = 0; i < st; i++) sum += nums[i];
	for(int i = 0; i < n; i++) sum += nums[i + st];
	std::printf("%lld\n", sum);
	return 0;
}