#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

char a[N][N];
int n, m, A, B;

void print() {
	puts("YES");
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) putchar(a[i][j]);
		putchar('\n');
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &A, &B);
	if(A * 2 + B * 2 > n * m) { puts("NO"); return 0; }
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = '.';
	if((m & 1) && B) for(int i = 1; i < n && B; i += 2) a[i][m] = '^', a[i + 1][m] = 'v', B--;
	if((n & 1) && A) for(int j = 1; j < m && A; j += 2) a[n][j] = '<', a[n][j + 1] = '>', A--;
	for(int i = 1; i < n; i += 2)
		for(int j = 1; j < m; j += 2)
			if(A >= 2) a[i][j] = a[i + 1][j] = '<', a[i][j + 1] = a[i + 1][j + 1] = '>', A -= 2;
			else if(B >= 2) a[i][j] = a[i][j + 1] = '^', a[i + 1][j] = a[i + 1][j + 1] = 'v', B -= 2;
	if(A || B) { // now A <= 1 && B <= 1
		if(A)
			for(int i = 1; i < n && A; i++)
				for(int j = 1; j < m && A; j++)
					if(a[i][j] == '.' && a[i][j + 1] == '.')
						a[i][j] = '<', a[i][j + 1] = '>', A--;
		if(B)
			for(int i = 1; i < n && B; i++)
				for(int j = 1; j < m && B; j++)
					if(a[i][j] == '.' && a[i + 1][j] == '.')
						a[i][j] = '^', a[i + 1][j] = 'v', B--;
	}
	if(A == 0 && B == 0) { print(); return 0; }
	if(n <= 2 || m <= 2) { puts("NO"); return 0; }
	A += (a[n - 2][m - 2] == '<') + (a[n - 1][m - 1] == '>') + (a[n][m - 1] == '>');
	B += (a[n - 2][m - 2] == '^') + (a[n - 1][m - 1] == 'v') + (a[n - 1][m] == 'v');
	for(int i = n - 2; i <= n; i++) for(int j = m - 2; j <= m; j++) a[i][j] = '.';
	if(A == 2 && B == 2) {
		a[n - 2][m - 2] = '^', a[n - 2][m - 1] = '<', a[n - 2][m - 0] = '>';
		a[n - 1][m - 2] = 'v', a[n - 1][m - 1] = '.', a[n - 1][m - 0] = '^';
		a[n - 0][m - 2] = '<', a[n - 0][m - 1] = '>', a[n - 0][m - 0] = 'v';
		print();
		return 0;
	}
	puts("NO");
	return 0;
}