#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int S = (1 << 6) + 5;

char a[N];
int n, m;

bool f[N][6 * N][S];
int last[N][6 * N][S];

int size(int s) {
	int ret = 0;
	for(int i = 0; i < 6; i++) ret += (s >> i & 1);
	return ret;
}

bool check(int s) {
	if((s & 1) && (s & 2)) return false;
	if((s & 2) && (s & 4)) return false;
	if((s & 8) && (s & 16)) return false;
	if((s & 16) && (s & 32)) return false;
	return true;
}

bool check(int t, int s) {
	if((s & 1) && ((t & 1) | (t & 2))) return false;
	if((s & 2) && ((t & 1) | (t & 2) | (t & 4))) return false;
	if((s & 4) && ((t & 2) | (t & 4))) return false;
	if((s & 8) && ((t & 8) | (t & 16))) return false;
	if((s & 16) && ((t & 8) | (t & 16) | (t & 32))) return false;
	if((s & 32) && ((t & 16) | (t & 32))) return false;
	return true;
}

void print(int i, int j, int s) {
	// printf("print(%d, %d, %d)\n", i, j, s);
	if(!i) return;
	print(i - 1, j - size(s), last[i][j][s]);
	for(int r = 0; r < 6; r++)
		if(s & (1 << r))
			printf("%d%c\n", i, 'A' + 5 - r);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		char a1, a2, a3, a4, a5, a6;
		scanf("\n%c%c%c|_|%c%c%c", &a1, &a2, &a3, &a4, &a5, &a6);
		if(a1 == '.') a[i] |= 1 << 5;
		if(a2 == '.') a[i] |= 1 << 4;
		if(a3 == '.') a[i] |= 1 << 3;
		if(a4 == '.') a[i] |= 1 << 2;
		if(a5 == '.') a[i] |= 1 << 1;
		if(a6 == '.') a[i] |= 1 << 0;
	}
	int U = (1 << 6) - 1;
	f[0][0][0] = true;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= m; j++) 
			for(int s = a[i]; ; s = (s - 1) & a[i]) {
				if(size(s) <= j && check(s))
					for(int t = 0; t <= U && !f[i][j][s]; t++)
						if(check(t, s) && f[i - 1][j - size(s)][t])
							f[i][j][s] = true, last[i][j][s] = t;
				if(!s) break;
			}
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 0; j <= m; j++)
	// 		for(int s = 0; s <= U; s++)
	// 			if(f[i][j][s])
	// 				printf("f[%d][%d][%d] = true, last = f[%d][%d][%d]\n", i, j, s, i - 1, j - size(s), last[i][j][s]);
	for(int s = a[n]; ; s = (s - 1) & a[n]) {
		if(f[n][m][s]) {
			puts("POBEDA");
			print(n, m, s);
			return 0;
		}
		if(!s) break;
	}
	puts("PORAZHENIE");
	return 0;
}