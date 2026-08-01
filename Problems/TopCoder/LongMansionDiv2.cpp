#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;
typedef long long LL;

const int N = 1000 + 5;

int a[N];
int n, m;

class LongMansionDiv2 {
public:
	LL minimalTime(int m_, vector<int> a_) {
		n = a_.size(), m = m_;
		for(int i = 1; i <= n; i++) a[i] = a_[i - 1];
		LL sum = 0, mn = 0x3f3f3f3f3f3f3f3fLL;
		for(int i = 1; i <= n; i++) sum += a[i], mn = std::min(mn, (LL)a[i]);
		return sum + mn * (m - 1);
	} 
};

int main() {
	LongMansionDiv2 T;
	printf("%lld\n", T.minimalTime(1, {1}));
	return 0;
}