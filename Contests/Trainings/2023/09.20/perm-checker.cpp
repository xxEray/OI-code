#include <bits/stdc++.h>

const int N = 17;
const int INF = 0x3f3f3f3f;

int n, K;
int dis[N][N];

int seq[N];
int solve(FILE *file) {
	int val;
	fscanf(file, "%d", &val);
	if(val == -1) return -1;
	seq[1] = val;
	for(int i = 2; i < n; i++) fscanf(file, "%d", &seq[i]);
	for(int i = 1; i < n; i++) seq[i]++;
	int ret = dis[1][seq[1]] + dis[seq[n - 1]][1];
	for(int i = 1; i < n - 1; i++) ret += dis[seq[i]][seq[i + 1]];
	return ret;
}

int main() {
	FILE *fin = fopen("perm.in", "r");
	FILE *fout = fopen("perm.out", "r");
	FILE *fans = fopen("perm.ans", "r");
	int T;
	fscanf(fin, "%d", &T);
	while(T--) {
		fscanf(fin, "%d%d", &n, &K);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : INF);
		for(int i = 1; i < n; i++) { int u, v; fscanf(fin, "%d%d", &u, &v); dis[u][v] = dis[v][u] = 1; }
		for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
		int out = solve(fout), ans = solve(fans);
		if((ans == -1 && out != -1) || (ans != -1 && out != K)) printf("out = %d, ans = %d, K = %d\n", out, ans, K);
		else puts("correct");
	}
	return 0;
}