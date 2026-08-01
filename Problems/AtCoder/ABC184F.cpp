#include <cstdio>
#include <set>

const int N = 40 + 5;
typedef long long LL;

LL a[N];
int n, m;

int n1, n2;

std::set<LL> st1, st2;

void searchhalf1(int ind, LL total) {
	if(ind > n1) { st1.insert(total); return; }
	searchhalf1(ind + 1, total);
	if(total + a[ind] <= m) searchhalf1(ind + 1, total + a[ind]);
}

void searchhalf2(int ind, LL total) {
	if(ind < n2) { st2.insert(total); return; }
	searchhalf2(ind - 1, total);
	if(total + a[ind] <= m) searchhalf2(ind - 1, total + a[ind]);
}

int main() {
	std::scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::scanf("%lld", &a[i]);
	n1 = n / 2, n2 = n1 + 1;
	searchhalf1(1, 0);
	// std::printf("Totals in [%d .. %d]: ", 1, n1);
	// for(const LL &num : st1) std::printf("%lld ", num);
	// std::printf("\nTotals in [%d .. %d]: ", n2, n);
	// for(const LL &num : st2) std::printf("%lld ", num);
	// std::printf("\n");
	searchhalf2(n, 0);
	// std::printf("Totals in [%d .. %d]: ", 1, n1);
	// for(const LL &num : st1) std::printf("%lld ", num);
	// std::printf("\nTotals in [%d .. %d]: ", n2, n);
	// for(const LL &num : st2) std::printf("%lld ", num);
	// std::printf("\n");
	LL ans = 0;
	for(const LL &num : st1) ans = std::max(ans, num + *--st2.upper_bound(m - num));
	std::printf("%lld\n", ans);
	return 0;
}