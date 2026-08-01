#include <cstdio>

const int N = 5000 + 5;

int n;
int a[N];

int pre[N], f[N][N];

int main() {
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) std::scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + (a[i] == 0);
	for(int i = 1; i <= n; i++) f[i][i] = 0;
	for(int len = 1; len <= n; len++)
		for(int l = 1; l + len <= n; l++) {
			int r = l + len;
		}
	return 0;
}