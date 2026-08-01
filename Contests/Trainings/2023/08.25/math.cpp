#include <bits/stdc++.h>

const int N = 5e4 + 5;

int n, Q;
int a[N];

int calc(std::vector<int> vct) {
	int ret = 0, sz = vct.size();
	if(sz == 1) return vct[0];
	for(int i = 2; i < sz; i++) {
		auto tmp = vct;
		int arr[3] = {tmp[i - 2], tmp[i - 1], tmp[i]};
		std::sort(arr, arr + 3);
		tmp[i] = arr[1];
		tmp.erase(tmp.begin() + i - 2, tmp.begin() + i);
		ret = std::max(ret, calc(tmp));
	}
	return ret;
}

int main() {
#ifndef DEBUG
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d",  &Q);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		std::vector<int> vct;
		for(int i = l; i <= r; i++) vct.push_back(a[i]);
		printf("%d\n", calc(vct));
	}
	return 0;
}