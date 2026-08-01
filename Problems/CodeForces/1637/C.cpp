#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
std::vector<int> even;
int n;

inline bool iseven(LL x) { return !(x & 1); }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		LL ans = 0;
		even.clear();
		for(int i = 2; i <= n - 1; i++) if(iseven(a[i])) even.push_back(i);
		if(even.empty()) {
			if(n == 3) { puts("-1"); continue; }
			int ind = -1;
			for(int i = 2; i <= n - 1; i++) if(a[i] > 1) ind = i;
			if(ind == -1) { puts("-1"); continue; }
			int ind2 = (ind == 2 ? 3 : 2);
			a[ind] -= 2, a[ind2]++, ans++, even.push_back(ind2);
		}
		int lo = 2, ro = n - 1;
		while(!even.empty()) {
			int ind = even.back();
			even.pop_back();
			while(lo < n && iseven(a[lo])) lo++;
			while(ro > 1 && iseven(a[ro])) ro--;
			if(lo > ind && ro < ind) continue;
			ans++;
			a[ind] -= 2;
			if(a[ind] >= 2) even.push_back(ind);
			if(lo < ind) a[lo]++, even.push_back(lo);
			if(ro > ind) a[ro]++, even.push_back(ro);
		}
		LL sum = 0;
		// for(int i = 2; i <= n - 1; i++) printf("%d ", a[i] + b[i]);
		for(int i = 2; i <= n - 1; i++) sum += a[i];
		assert(sum % 2 == 0);
		ans += sum / 2;
		printf("%lld\n", ans);
	}
	return 0;
}