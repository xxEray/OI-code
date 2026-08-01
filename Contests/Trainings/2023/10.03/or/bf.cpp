#include <bits/stdc++.h>

typedef long long LL;

LL p[100];

std::set<LL> st;

int main() {
	LL l, r;
	scanf("%lld%lld", &l, &r);
	for(int s = 1; s < (1 << (r - l + 1)); s++) {
		LL val = 0;
		for(int i = 0; i < r - l + 1; i++) if(s >> i & 1)
			val |= i + l;
		st.insert(val);
	}
	// puts("");
	// for(auto x : st) printf("%lld ", x);
	// puts("");
	printf("%lld\n", (LL)st.size());
	return 0;
}