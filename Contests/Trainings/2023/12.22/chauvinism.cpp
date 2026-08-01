#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
int a[N], b[N];

int aa[N];

bool check(LL x) {
	std::multiset<LL> st;
	LL base = 0, sum = 0;
	int cnt0 = 0;
	// printf("check(%lld)\n", x);
	for(int i = 1; i <= n; i++) {
		base += a[i];
		st.emplace(b[i] - a[i]), sum += b[i] - a[i];
		while(!st.empty() && base < 0) {
			if(base + *st.begin() <= 0) base += *st.begin(), sum -= *st.begin(), st.erase(st.begin()), cnt0++;
			else {
				LL v = *st.begin();
				sum -= std::abs(base), st.erase(st.begin()), st.emplace(v - std::abs(base)), base = 0;
			}
		}
		if(base < 0) base = 0;
		while(!st.empty() && base + sum > x) sum -= *st.rbegin(), st.erase(--st.end());
		if(base > x) return false;
		// printf("i = %d: (base=%lld, sum=%lld) ", i, base, sum);
		// for(int _ = 1; _ <= cnt0; _++) printf("0 ");
		// for(const auto &v : st) printf("%lld ", v);
		// puts("");
	}
	return cnt0 + (int)st.size() >= n - K;
}

char out[N];
bool ban[N];
void get_answer(LL x) {
	std::set<std::pair<LL, int>> st, st0;
	for(int i = 1; i <= n; i++) K += ban[i];
	LL base = 0, sum = 0;
	// printf("check(%lld)\n", x);
	for(int i = 1; i <= n; i++) {
		base += a[i];
		if(!ban[i]) st.emplace(b[i] - a[i], i), sum += b[i] - a[i];
		while(!st.empty() && base < 0) {
			if(base + st.begin()->first <= 0) base += st.begin()->first, sum -= st.begin()->first, st0.emplace(0, st.begin()->second), st.erase(st.begin());
			else {
				auto [v, id] = *st.begin();
				sum -= std::abs(base), st.erase(st.begin()), st.emplace(v - std::abs(base), id), base = 0;
			}
		}
		if(base < 0) base = 0;
		while(!st.empty() && base + sum > x) sum -= st.rbegin()->first, st.erase(--st.end());
		assert((!st.empty() || sum == 0) && base <= x);
	}
	// for(const auto &[v, id] : st0) printf("(%lld,%d) ", v, id);
	// for(const auto &[v, id] : st) printf("(%lld,%d) ", v, id);
	while(!st.empty() && (int)st0.size() + (int)st.size() > n - K) st.erase(--st.end());
	while(!st0.empty() && (int)st0.size() + (int)st.size() > n - K) st0.erase(--st0.end());
	for(int i = 1; i <= n; i++) out[i] = 'A';
	for(const auto &[_, id] : st) out[id] = 'B';
	for(const auto &[_, id] : st0) out[id] = 'B';
	for(int i = 1; i <= n; i++) if(ban[i]) out[i] = 'B';
}

int main() {
	// freopen("chauvinism.in", "r", stdin);
	// freopen("chauvinism.out", "w", stdout);
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	bool flipped = false;
	int K_ = 0;
	for(int i = 1; i <= n; i++) if(a[i] < b[i]) K_++;
	if(K_ < K) {
		flipped = true;
		K_ = n - K_, K = n - K;
		for(int i = 1; i <= n; i++) std::swap(a[i], b[i]);
	}
	for(int i = 1; i <= n; i++) if(a[i] > b[i]) ban[i] = true, a[i] = b[i];
	// printf("a: "); for(int i = 1; i <= n; i++) printf("%2d ", a[i]); puts("");
	// printf("b: "); for(int i = 1; i <= n; i++) printf("%2d ", b[i]); puts("");
	LL l = 0, r = 2.01e14;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);
	get_answer(l);
	if(flipped) for(int i = 1; i <= n; i++) out[i] = 'A' + 'B' - out[i];
	out[n + 1] = 0;
	puts(out + 1);
	return 0;
} /*
2 1
-1 2 
0 0 
*/