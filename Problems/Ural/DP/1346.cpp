#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int f[N][2];

void input() {
	int x, y;
	scanf("%d%d", &x, &y);
	n = y - x + 1;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
}

int cnt = 0;

void solve() {
	for(int i = 0; i <= n; i++) f[i][0] = f[i][1] = INF;
	f[0][0] = f[0][1] = f[1][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++) {
		if(a[i - 1] < a[i]) {
			f[i][0] = std::min(f[i][0], std::min(f[i - 1][0], f[i - 1][1] + 1));
			f[i][1] = std::min(f[i][1], std::min(f[i - 1][0] + 1, f[i - 1][1] + 1));
		} else if(a[i - 1] > a[i]) {
			f[i][1] = std::min(f[i][1], std::min(f[i - 1][1], f[i - 1][0] + 1));
			f[i][0] = std::min(f[i][0], std::min(f[i - 1][0] + 1, f[i - 1][1] + 1));
		} else {
			f[i][0] = f[i - 1][0];
			f[i][1] = f[i - 1][1];
		}
		// printf("f[%d] = %d %d\n", i, f[i][0], f[i][1]);
	}
}

void output() {
	printf("%d\n", std::min(f[n][0], f[n][1]));
}

int main() {
	input();
	solve();
	output();
	return 0;
} /*
1 5
1 1 0 0 1
*/