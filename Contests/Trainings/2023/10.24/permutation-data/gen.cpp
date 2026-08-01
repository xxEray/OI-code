#include "testlib.h"
#include <cassert>

const int N = 1e5 + 5;

int a[N], b[N], mp[N];

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = opt<int>("n");
	printf("%d\n", n);
	int upper = opt<int>("upper");
	for(int i = 1; i <= n; i++) mp[i] = i;
	shuffle(mp + 1, mp + n + 1);
	std::vector<int> vct;
	for(int x = 0; x < n;) {
		int v = rnd.next(0, upper / 2) == 0 ? rnd.next(1, upper) : 1;
		v = std::min(v, n - x);
		vct.push_back(v), x += v;
	}
	for(int x = 0, i = 0; i < (int)vct.size(); x += vct[i], i++)
		for(int j = x + 1; j <= x + vct[i]; j++)
			a[mp[j]] = b[mp[j]] = (j == x + vct[i] ? mp[x + 1] : mp[j + 1]);
	int T = n / 6;
	while(T--) {
		int u = rnd.next(1, n), v = rnd.next(1, n);
		if(rnd.next(0, 1)) std::swap(a[u], a[v]);
		else std::swap(b[u], b[v]);
	}
	for(int i = 1; i <= n; i++) printf("%d ", a[i]);
	puts("");
	for(int i = 1; i <= n; i++) printf("%d ", b[i]);
	puts("");
	return 0;
}