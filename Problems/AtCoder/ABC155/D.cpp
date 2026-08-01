#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n; LL K;
std::vector<LL> a, b;
LL cnt0;

LL ceil_div(LL x, LL y) { if(y < 0) x = -x, y = -y; return x < 0 ? x / y : (x + y - 1) / y; }
LL floor_div(LL x, LL y) { if(y < 0) x = -x, y = -y; return x < 0 ? (x - y + 1) / y : x / y; }
LL calc(LL val) {
	LL ret = 0;
	if(val >= 0) {
		ret += (LL)a.size() * (LL)b.size() + cnt0 * (n - cnt0) + cnt0 * (cnt0 - 1) / 2;
		for(int i = 0; i < (int)a.size(); i++) ret += a.end() - std::max(std::lower_bound(a.begin(), a.end(), ceil_div(val, a[i])), a.begin() + i + 1);
		for(int i = 0; i < (int)b.size(); i++) ret += std::min(std::upper_bound(b.begin(), b.end(), floor_div(val, b[i])), b.begin() + i) - b.begin();
	} else {
		for(int i = 0; i < (int)a.size(); i++) ret += b.end() - std::lower_bound(b.begin(), b.end(), ceil_div(val, a[i]));
		// for(int i = 0; i < (int)b.size(); i++) ret += std::upper_bound(a.begin(), a.end(), floor_div(val, b[i])) - a.begin();
	}
	// LL res = 0;
	// std::vector<LL> vct;
	// vct.insert(vct.end(), a.begin(), a.end()), vct.insert(vct.end(), b.begin(), b.end());
	// for(int _ = 1; _ <= cnt0; _++) vct.push_back(0);
	// for(int i = 0; i < (int)vct.size(); i++) for(int j = i + 1; j < (int)vct.size(); j++) res += (vct[i] * vct[j] <= val);
	// if(ret != res) { printf("calc(%lld) = %lld instead of %lld\n", val, ret, res); exit(0); }
	// printf("calc(%lld) = %lld\n", val, ret);
	return ret;
}

int main() {
	scanf("%d%lld", &n, &K);
	for(int i = 1; i <= n; i++) {
		LL x;
		scanf("%lld", &x);
		if(x < 0) a.push_back(x);
		else if(x > 0) b.push_back(x);
		else cnt0++;
	}
	std::sort(a.begin(), a.end()), std::sort(b.begin(), b.end());
	LL l = -1e18, r = 1e18;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(calc(mid) >= K) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
}