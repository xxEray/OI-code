#include <cstdio>
#include <algorithm>
#include <deque>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

std::deque<LL> posi, nega;
int n, m;

bool choose[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		LL x;
		scanf("%lld", &x);
		if(x < 0) nega.push_back(-x);
		else posi.push_back(x);
	}
	std::sort(posi.begin(), posi.end(), [](LL x, LL y) { return x > y; });
	std::sort(nega.begin(), nega.end(), [](LL x, LL y) { return x > y; });
	if((int)posi.size() == 0 && (m & 1)) {
		LL prod = 1;
		while(m--) {
			prod = (prod * nega.back()) % MOD;
			nega.pop_back();
		}
		printf("%lld\n", (-prod + MOD) % MOD);
		return 0;
	}
	bool tonega = false;
	LL prod = 1;
	if(m & 1) prod = posi.front(), posi.pop_front(), m--;
	while(m) {
		if((int)posi.size() < 2 && (int)nega.size() < 2) {
			prod = prod * posi.front() % MOD;
			posi.pop_front();
			prod = prod * nega.front() % MOD;
			nega.pop_front();
			tonega = true;
		} else if((int)posi.size() < 2) {
			prod = prod * nega.front() % MOD;
			nega.pop_front();
			prod = prod * nega.front() % MOD;
			nega.pop_front();
		} else if((int)nega.size() < 2) {
			prod = prod * posi.front() % MOD;
			posi.pop_front();
			prod = prod * posi.front() % MOD;
			posi.pop_front();
		} else {
			LL c1 = nega.at(0) * nega.at(1);
			LL c2 = posi.at(0) * posi.at(1);
			if(c1 > c2) {
				prod = prod * nega.front() % MOD;
				nega.pop_front();
				prod = prod * nega.front() % MOD;
				nega.pop_front();
			} else {
				prod = prod * posi.front() % MOD;
				posi.pop_front();
				prod = prod * posi.front() % MOD;
				posi.pop_front();
			}
		}
		m -= 2;
	}
	printf("%lld\n", tonega ? (-prod + MOD) % MOD : prod);
	// printf("%lld\n", prod);
	return 0;
}