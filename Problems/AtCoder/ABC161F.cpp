#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>

typedef long long LL;

std::set<LL> ans;
LL n;

bool check(LL x) {
	LL t = n;
	while(t % x == 0) t /= x;
	return t % x == 1;
}

int main() {
	scanf("%lld", &n);
	if(n == 2) { puts("1"); return 0; }
	ans.insert(n), ans.insert(n - 1);
	LL sqn = sqrt(n);
	for(LL i = 2; i <= sqn; i++)
		if((n - 1) % i == 0)
			ans.insert(i), ans.insert((n - 1) / i);
	for(LL i = 2; i <= sqn; i++)
		if(check(i)) ans.insert(i);
	printf("%d\n", (int)ans.size());
	// for(LL x : ans) printf("%lld ", x);
	return 0;
}