#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2000 + 5;

struct Range { int l, r, id; } a[N];
int n;

int tmp[N << 1];
void preprocess() {
	for(int i = 1; i <= n; i++) tmp[i * 2 - 1] = a[i].l, tmp[i * 2] = a[i].r;
	std::sort(tmp + 1, tmp + 2 * n + 1);
	int n_ = std::unique(tmp + 1, tmp + 2 * n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].l = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i].l) - tmp;
	for(int i = 1; i <= n; i++) a[i].r = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i].r) - tmp;
}

std::vector<int> v[N << 1];
int f[N << 1][N << 1], last[N << 1][N << 1], cnt[N << 1][N << 1];

void print(int l, int r) {
	if(l > r) return;
	cnt[l][r] = -1;
	int i = last[l][r];
	if(i == -1) print(l + 1, r);
	else if(i == -2) print(l, r - 1);
	else print(l, i), print(i, r);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); a[i].l = x - y, a[i].r = x + y, a[i].id = i; }
	preprocess();
	int rlim = 0;
	for(int i = 1; i <= n; i++) v[a[i].l].push_back(a[i].r), cnt[a[i].l][a[i].r]++, rlim = std::max(rlim, a[i].r);
	// std::sort(a + 1, a + n + 1, [](Range x, Range y) { return x.r == y.r ? x.l > y.l : x.r < y.r; });
	// for(int i = 1; i <= n; i++) printf("%d -> [%d, %d]\n", a[i].id, a[i].l, a[i].r);
	for(int len = 1; len <= rlim; len++)
		for(int i = 1; i + len - 1 <= rlim; i++) {
			int j = i + len - 1;
			f[i][j] = f[i + 1][j], last[i][j] = -1;
			if(f[i][j] < f[i][j - 1]) f[i][j] = f[i][j - 1], last[i][j] = -2;
			for(int k : v[i])
				if(k < j && f[i][j] < f[i][k] + f[k][j])
					f[i][j] = f[i][k] + f[k][j], last[i][j] = k;
			f[i][j] += cnt[i][j];
			// printf("f[%d][%d] = %d (%d)\n", i, j, f[i][j], cnt[i][j]);
		}
	printf("%d\n", f[1][rlim]);
	print(1, rlim);
	for(int i = 1; i <= n; i++) if(cnt[a[i].l][a[i].r] == -1) printf("%d ", a[i].id);
	return 0;
}