#include <bits/stdc++.h>

const int N = 4000 + 5;

char a[N][N];
int n, m;

char b[N][N];

int main() {
#ifndef DEBUG
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	auto check = [&](int offset, bool flip) -> void {
		bool flag = true;
		for(int i = offset; i <= n; i += 2) {
			bool fl[2][2] = {{true, true}, {true, true}};
			for(int j = 1; j <= m; j++) fl[0][j & 1] &= (a[i][j] != '1'), fl[1][j & 1] &= (a[i][j] != '0');
			if(fl[0][0] && fl[1][1]) {
				for(int j = 1; j <= m; j++) b[i][j] = ((j & 1) ? '1' : '0');
			} else if(fl[0][1] && fl[1][0]) {
				for(int j = 1; j <= m; j++) b[i][j] = ((j & 1) ? '0' : '1');
			} else flag = false;
		}
		for(int i = 3 - offset; i <= n; i += 2) {
			bool fl = true;
			for(int j = 1; j <= m; j++) fl &= (a[i][j] != '1');
			if(fl) {
				for(int j = 1; j <= m; j++) b[i][j] = '0';
			} else flag = false;
		}
		if(flag) {
			if(flip) {
				for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[j][i] = b[i][j], b[i][j] = 0;
				std::swap(n, m);
				for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) b[i][j] = a[i][j];
			}
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) putchar(b[i][j]);
				puts("");
			}
			exit(0);
		}
	};
	check(1, false), check(2, false);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) b[j][i] = a[i][j], a[i][j] = 0;
	std::swap(n, m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = b[i][j];
	check(1, true), check(2, true);
	return 0;
} /*
3 5
??00?
0?0?0
0?0?0
*/
