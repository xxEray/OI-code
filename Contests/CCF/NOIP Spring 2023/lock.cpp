#include <cstdio>
#include <algorithm>

const int N = 3e4 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
int a[5][N];

int calc(int arr[5][N], int i) { return *std::max_element(arr[i] + 1, arr[i] + n + 1) - *std::min_element(arr[i] + 1, arr[i] + n + 1); }

int b[5][N];

namespace Solve_K1 {
	void main() {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[0][i]);
		printf("%d\n", calc(a, 0));
	}
}

namespace Solve_K2 {
	void main() {
		scanf("%d", &n);
		for(int i = 0; i < K; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
		for(int i = 1; i <= n; i++) if(a[0][i] > a[1][i]) std::swap(a[0][i], a[1][i]);
		printf("%d\n", std::max(calc(a, 0), calc(a, 1)));
	}
}

namespace Solve_K3 {
	int c[N];
	int mxi, mxj, mni, mnj;
	bool check(int x) {
		for(int i = 0; i <= 30001; i++) c[i] = 0;
		for(int i = 1; i <= n; i++)
		int mx = -INF, mn = INF;
			for(int j = 0; j < K; j++) {
				if()
			}
	}
	void main() {
		int mx = -INF, mn = INF;
		scanf("%d", &n);
		for(int i = 0; i < K; i++) for(int j = 1; j <= n; j++) {
			scanf("%d", &a[i][j]);
			if(a[i][j] < mn) mn = a[i][j], mni = i, mnj = j;
			if(a[i][j] > mx) mx = a[i][j], mxi = i, mxj = j;
		}
		int thi = 3 - mni - mxi;
		int l = 0, r = 3e4;
		if(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
}

namespace Solve_K4 {
	void main() {
		scanf("%d", &n);
		for(int i = 0; i < K; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
		
	}
}

int main() {
// #ifndef DEBUG
	freopen("lock.in", "r", stdin);
	freopen("lock.out", "w", stdout);
// #endif
	int T; scanf("%d%d", &T, &K);
	if(K == 1) while(T--) Solve_K1::main();
	else if(K == 2) while(T--) Solve_K2::main();
	else if(K == 3) while(T--) Solve_K3::main();
	else if(K == 4) while(T--) Solve_K4::main();
	return 0;
}