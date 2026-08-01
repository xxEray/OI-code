#include <bits/stdc++.h>

typedef long long LL;

const int N = 100;
const int M = 1e4;

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("data.txt", "w", stdout);
	int n = N;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++, puts("")) for(int j = i; j <= n; j++) printf("%d ", rand() % 1001);
	std::vector<int> tmp;
	for(int i = 1; i <= n; i++) tmp.push_back((rand() << 15 | rand()) % (M - n) + 1);
	std::sort(tmp.begin(), tmp.end());
	for(int i = 1; i <= n; i++) {
		int k = std::max(tmp[i - 1] - (i > 1 ? tmp[i - 2] : 0), 1);
		printf("%d\n", k);
		while(k--) printf("%d %lld\n", (rand() << 15 | rand()) % 100000001, ((LL)rand() << 45 | (LL)rand() << 30 | rand() << 15 | rand()) % 10000000000001);
	}
	return 0;
}