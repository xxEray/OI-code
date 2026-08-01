#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 40 + 5;

int cnt[4];
int n, m;
int st;

int f[N][N][N][N][4];

int get() {
	char s[5];
	scanf("%s", s);
	if(!strcmp(s, "AA")) return 0;
	else if(!strcmp(s, "AB")) return 1;
	else if(!strcmp(s, "BA")) return 2;
	else if(!strcmp(s, "BB")) return 3;
	else exit(-1);
}

int main() {
	scanf("%d%d", &n, &m);
	st = get();
	for(int i = 1; i <= n; i++) cnt[get()]++;
	if(st == 0) f[1][0][0][0][0] = 1, cnt[0]++;
	else if(st == 1) f[0][1][0][0][1] = 1, cnt[1]++;
	else if(st == 2) f[0][0][1][0][2] = 1, cnt[2]++;
	else if(st == 3) f[0][0][0][1][3] = 1, cnt[3]++;
	int ret = 0;
	for(int i = 0; i <= cnt[0]; i++)
		for(int j = 0; j <= cnt[1]; j++)
			for(int k = 0; k <= cnt[2]; k++)
				for(int r = 0; r <= cnt[3]; r++) {
					/*
					0 -- AA
					1 -- AB
					2 -- BA
					3 -- BB
					*/
					if(i) f[i][j][k][r][0] += f[i - 1][j][k][r][0], f[i][j][k][r][0] += f[i - 1][j][k][r][2];
					if(j) f[i][j][k][r][1] += f[i][j - 1][k][r][0], f[i][j][k][r][1] += f[i][j - 1][k][r][2];
					if(k) f[i][j][k][r][2] += f[i][j][k - 1][r][1], f[i][j][k][r][2] += f[i][j][k - 1][r][3];
					if(r) f[i][j][k][r][3] += f[i][j][k][r - 1][1], f[i][j][k][r][3] += f[i][j][k][r - 1][3];
					if(i + j + k + r == m + 1)
						for(int c = 0; c <= 3; c++)
							ret = std::max(ret, f[i][j][k][r][c]);
				}
	if(ret) printf("YES\n%d", ret);
	else puts("NO");
	return 0;
}