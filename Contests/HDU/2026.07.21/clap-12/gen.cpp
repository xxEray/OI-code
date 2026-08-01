#include <bits/stdc++.h>
#include "testlib.h"

typedef long long LL;

const int N = 100 + 5;

LL u[N], v[N];

int a[N][N];

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	FILE *fans = fopen("ans.txt", "w");
	int T = 3;
	printf("%d\n", T);
	while(T--) {
		int n = rnd.next(2, 5), K = rnd.next(2, 5);
		for(int i = 1; i <= n; i++) v[i] = rnd.next(-1000000000, 1000000000);
		std::vector<std::pair<int, int>> vct;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
			if(rnd.next(0, 1)) vct.emplace_back(i, j);
		for(int i = 1; i <= n; i++) u[i] = v[i];
		for(auto [x, y] : vct) u[y] += v[x] * K;
		printf("%d %lld %d\n", n, K, (int)vct.size());
		for(int i = 1; i <= n; i++) printf("%lld ", u[i]);
		puts("");
		for(auto [x, y] : vct) printf("%d ", y);
		puts("");
		for(auto [x, y] : vct) printf("%d ", x);
		puts("");
		for(int i = 1; i <= n; i++) fprintf(fans, "%lld ", v[i]);
		fprintf(fans, "\n");
	}
	return 0;
}