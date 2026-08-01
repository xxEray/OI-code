#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

typedef long long LL;

vector<int> cnt, digits;
int n, m;

LL ans = 0x3f3f3f3f3f3f3f3fLL;

bool tag[20];
void dfs(int i, int j) {
	if(j == n + 1) {
		LL num[2] = {0, 0};
		for(int k = 0; k < n + m; k++) num[tag[k]] = num[tag[k]] * 10 + digits[k];
		// if(num[0] * num[1] < ans) printf("%lld * %lld = %lld\n", num[0], num[1], num[0] * num[1]);
		ans = std::min(ans, num[0] * num[1]);
		return;
	}
	if(i == n + m) return;
	for(int k = i; k < n + m; k++) tag[k] = 1, dfs(k + 1, j + 1), tag[k] = 0;
}

class MinProduct {
public:
	LL findMin(vector<int> amount_, int blank1_, int blank2_) {
		cnt = amount_, n = blank1_, m = blank2_;
		for(int i = 0; (int)digits.size() < n + m; ) {
			while(cnt[i] == 0) i++;
			digits.push_back(i), cnt[i]--;
		}
		dfs(0, 1);
		return ans;
	}
};

int main() {
	MinProduct T;
	printf("%lld\n", T.findMin({0, 0, 0, 0, 0, 0, 0, 0, 18}, 9, 9));
	return 0;
}