#include <bits/stdc++.h>

const int N = 4;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }

std::array<int, 4> out[N + 5];
int cnt = 0, cnt2;
int dfs(int l, int r) {
	if(l == r) {
		int now = ++cnt2;
		out[now][0] = l, out[now][1] = r;
		return now;
	}
	int mid = rand(l, r - 1);
	int now = ++cnt;
	int ls = dfs(l, mid), rs = dfs(mid + 1, r);
	out[now][0] = l, out[now][1] = r, out[now][2] = ls, out[now][3] = rs;
	return now;
}

int main(int argc, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("entrench.in", "w", stdout);
	int n = rand(1, N), m = rand(1, N);
	printf("%d %d 0\n", n, m);
	cnt2 = n - 1;
	dfs(1, n);
	for(int i = 1; i <= 2 * n - 1; i++) printf("%d %d %d %d\n", out[i][0], out[i][1], out[i][2], out[i][3]);
	while(m--) {
		int t = rand(1, 2);
		if(t == 1) printf("1 %d\n", rand(1, n));
		else printf("2 %d %d\n", rand(1, n), rand(1, n));
	}
	return 0;
}