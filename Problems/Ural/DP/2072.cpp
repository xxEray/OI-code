#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;
int a[N];

int least[N][2];
LL f[N][2];

int tmp[N];
void preprocess() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 1);
	m = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + m + 1, a[i]) - tmp;
}


int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	preprocess();
	for(int i = 1; i <= n; i++) {
		if(least[a[i]][0] == 0) least[a[i]][0] = i;
		least[a[i]][1] = i;
	}
	// for(int i = 1; i <= n; i++) printf("%d%c", a[i], i == n ? '\n' : ' ');
	// for(int i = 1; i <= m; i++) printf("least[%d]: %d, %d\n", i, least[i][0], least[i][1]);
	least[0][0] = least[0][1] = 1;
	f[0][0] = f[0][1] = 0;
	for(int i = 1; i <= m; i++) {
		#define val(i, x, y) f[i - 1][y] + std::abs(least[i - 1][y] - least[i - 1][!y]) + std::abs(least[i][x] - least[i - 1][!y])
		f[i][0] = std::min(val(i, 0, 0), val(i, 0, 1));
		f[i][1] = std::min(val(i, 1, 0), val(i, 1, 1));
	}
	#define answer(t) f[m][t] + std::abs(least[m][t] - least[m][!t])
	printf("%lld\n", std::min(answer(0), answer(1)) + n);
	return 0;
} /*
6
3 2 5 6 2 5
*/