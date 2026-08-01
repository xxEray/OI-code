#include <bits/stdc++.h>

const int N = 20 + 5;

int n, m;
int a[N][N], b[N][N];

int p[N], q[N];

int get_inv(int *arr, int len) {
	int ret = 0;
	for(int i = 1; i <= len; i++)
		for(int j = 1; j < i; j++)
			ret += arr[j] > arr[i];
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &b[i][j]);
	for(int i = 1; i <= n; i++) p[i] = i;
	for(int i = 1; i <= m; i++) q[i] = i;
	int ans = 10000;
	do {
		do {
			bool flag = true;
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) flag &= (a[p[i]][q[j]] == b[i][j]);
			if(flag) ans = std::min(ans, get_inv(p, n) + get_inv(q, m));
		} while(std::next_permutation(q + 1, q + m + 1));
	} while(std::next_permutation(p + 1, p + n + 1));
	printf("%d\n", ans == 10000 ? -1 : ans);
	return 0;
}