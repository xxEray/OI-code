#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;

int a[N], b[N];
int tmp[N];

int main() {
	scanf("%*d%*d%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	int n_;
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 1);
	n_ = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i]) - tmp;
	for(int i = 1; i <= n; i++) tmp[i] = b[i];
	std::sort(tmp + 1, tmp + n + 1);
	n_ = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) b[i] = std::lower_bound(tmp + 1, tmp + n_ + 1, b[i]) - tmp;
	for(int i = 1; i <= n; i++) printf("%d %d\n", a[i], b[i]);
	return 0;
}