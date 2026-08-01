#include "testlib.h"
#include <random>

const int N = 2500 + 5;

int a[N][N], mxr[N], mxc[N];

int main(int argc, char *argv[]) {
	registerGen(argc, argv, 1);
	int n = rnd.next(1, opt<int>("n")), V = rnd.next(1, opt<int>("V"));
	std::vector<int> rands;
	int bd = round(pow(n, rnd.next(1.4, 1.6)));
	for(int i = 1; i <= bd; i++) rands.push_back(rnd.next(0, V));
	std::sort(rands.begin(), rands.end());
	rands.erase(std::unique(rands.begin(), rands.end()), rands.end());
	if(rands.empty()) rands.push_back(rnd.next(0, V));
	int m = 0;
	for(int i = 1; i <= n; i++) mxr[i] = mxc[i] = -1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(rnd.next(0, 1)) a[i][j] = -1;
		else a[i][j] = rnd.any(rands), mxr[i] = std::max(mxr[i], a[i][j]), mxc[j] = std::max(mxc[j], a[i][j]), m++;
	for(int i = 1; i <= n; i++) if(mxr[i] == -1) {
		int j = rnd.next(1, n);
		a[i][j] = rnd.any(rands), m++;
		mxr[i] = std::max(mxr[i], a[i][j]), mxc[j] = std::max(mxc[j], a[i][j]);
	}
	for(int j = 1; j <= n; j++) if(mxc[j] == -1) {
		int i = rnd.next(1, n);
		a[i][j] = rnd.any(rands), m++;
		mxr[i] = std::max(mxr[i], a[i][j]), mxc[j] = std::max(mxc[j], a[i][j]);
	}
	printf("%d %d %d\n", n, m, V);
	for(int i = 1; i <= n; i++) printf("%d ", mxr[i]);
	puts("");
	for(int i = 1; i <= n; i++) printf("%d ", mxc[i]);
	puts("");
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i][j] != -1) printf("%d %d\n", i, j);
	return 0;
}