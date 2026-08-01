#include <cstdio>
#include <cstring>

const int N = 1e5 + 5;

int a, b, c;
int n;

int dp[N][3][3][3], pre1[N][3][3][3], pre2[N][3][3][3];

void print1(int ind, int i, int j, int k) {
	int a = i, b = j, c = k;
	switch(pre1[ind][i][j][k]) { case 1: a++; break; case 2: b++; break; case 3: c++; break; }
	switch(pre2[ind][i][j][k]) { case 1: a--; break; case 2: b--; break; case 3: c--; break; }
	// printf("(%d, %d, %d)\n", a, b, c);
	if(ind > 1) print1(ind - 1, a, b, c);
	switch(pre2[ind][i][j][k]) { case 1: puts("A"); break; case 2: puts("B"); break; case 3: puts("C"); break; default: puts("Error"); }
}

void print2(int ind) {
	if(ind > 1) print2(ind - 1);
	switch(pre2[ind][0][0][0]) { case 1: puts("A"); break; case 2: puts("B"); break; case 3: puts("C"); break; default: puts("Error"); }
}

int main() {
	// freopen("in.txt", "r", stdin);
	scanf("%d%d%d%d", &n, &a, &b, &c);
	if(a + b + c == 2) {
		dp[0][a][b][c] = 1;
		for(int i = 1; i <= n; i++) {
			char s[3];
			scanf("%s", s);
			if(!strcmp(s, "AB")) {
				for(int a = 0; a <= 2; a++)
					for(int b = 0; b <= 2; b++)
						for(int c = 0; c <= 2; c++)
							if(a && dp[i - 1][a - 1][b + 1][c]) dp[i][a][b][c] = true, pre1[i][a][b][c] = 2, pre2[i][a][b][c] = 1;
							else if(b && dp[i - 1][a + 1][b - 1][c]) dp[i][a][b][c] = true, pre1[i][a][b][c] = 1, pre2[i][a][b][c] = 2;
			} else if(!strcmp(s, "AC")) {
				for(int a = 0; a <= 2; a++)
					for(int b = 0; b <= 2; b++)
						for(int c = 0; c <= 2; c++)
							if(a && dp[i - 1][a - 1][b][c + 1]) dp[i][a][b][c] = true, pre1[i][a][b][c] = 3, pre2[i][a][b][c] = 1;
							else if(c && dp[i - 1][a + 1][b][c - 1]) dp[i][a][b][c] = true, pre1[i][a][b][c] = 1, pre2[i][a][b][c] = 3;
			} else if(!strcmp(s, "BC")) {
				for(int a = 0; a <= 2; a++)
					for(int b = 0; b <= 2; b++)
						for(int c = 0; c <= 2; c++)
							if(b && dp[i - 1][a][b - 1][c + 1]) dp[i][a][b][c] = true, pre1[i][a][b][c] = 3, pre2[i][a][b][c] = 2;
							else if(c && dp[i - 1][a][b + 1][c - 1]) dp[i][a][b][c] = true, pre1[i][a][b][c] = 2, pre2[i][a][b][c] = 3;
			}
		}
		for(int i = 0; i <= 2; i++)
			for(int j = 0; j <= 2; j++)
				for(int k = 0; k <= 2; k++)
					if(i + j + k == 2 && dp[n][i][j][k]) {
						// printf("(%d, %d, %d)\n", i, j, k);
						puts("Yes");
						print1(n, i, j, k);
						return 0;
					}
		puts("No");
	} else {
		for(int i = 1; i <= n; i++) {
			char s[3];
			scanf("%s", s);
			if(!strcmp(s, "AB")) {
				if(!a && !b) { puts("No"); return 0; }
				if(a < b) a++, b--, pre1[i][0][0][0] = 2, pre2[i][0][0][0] = 1;
				else a--, b++, pre1[i][0][0][0] = 1, pre2[i][0][0][0] = 2;
			} else if(!strcmp(s, "AC")) {
				if(!a && !c) { puts("No"); return 0; }
				if(a < c) a++, c--, pre1[i][0][0][0] = 3, pre2[i][0][0][0] = 1;
				else a--, c++, pre1[i][0][0][0] = 1, pre2[i][0][0][0] = 3;
			} else if(!strcmp(s, "BC")) {
				if(!b && !c) { puts("No"); return 0; }
				if(b < c) b++, c--, pre1[i][0][0][0] = 3, pre2[i][0][0][0] = 2;
				else b--, c++, pre1[i][0][0][0] = 2, pre2[i][0][0][0] = 3;
			}
		}
		puts("Yes");
		print2(n);
	}
	return 0;
}