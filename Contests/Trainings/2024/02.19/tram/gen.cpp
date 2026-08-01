#include <bits/stdc++.h>

const int N = 5;
const int M = 20;

int rand(int l, int r) { return ((long long)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	// freopen("../tram.in", "w", stdout);
	int n = N, m = M;
	printf("%d %d\n", n, m);
	std::vector<int> vct;
	for(int i = 1; i <= m; i++) {
		int t;
		if((int)vct.size() == 2 * n) t = 2;
		else if(vct.empty()) t = 1;
		else t = rand() % 2;
		if(t == 1) puts("1"), vct.emplace_back(i);
		else {
			int j = rand() % (int)vct.size();
			printf("2 %d\n", vct[j]);
			vct.erase(vct.begin() + j);
		}
	}
	return 0;
}
