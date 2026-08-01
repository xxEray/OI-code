#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;

int n, Q;
LL a[N];

LL b[N];
LL calc() {
	for(int i = 1; i <= n; i++) b[i] = a[i];
	std::vector<int> vct;
	for(int i = 1; i <= n; i++) if(b[i] & 1) b[i]--, vct.emplace_back(i);
	LL ret = 0, sum = 0;
	for(int i = 1, j = 0; i <= n; i++) {
		while(b[i] && j < (int)vct.size() && 2 * i - 1 >= vct[j]) b[i] -= 2, j++, ret++;
	}
	for(int i = 1; i <= n; i++) sum += b[i];
	return ret + sum / 3;
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	while(Q--) {
		int k, x;
		scanf("%d%d", &k, &x);
		a[k] += x;
		assert(a[k] >= 0);
		printf("%lld\n", calc());
	}
	return 0;
}