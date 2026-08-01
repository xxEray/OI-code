#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

char s[N][N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n - 5; j++) {
		int cnt = 0;
		for(int k = 0; k <= 5; k++) cnt += (s[i][j + k] == '#');
		if(cnt >= 4) { puts("Yes"); return 0; }
	}
	for(int i = 1; i <= n - 5; i++) for(int j = 1; j <= n; j++) {
		int cnt = 0;
		for(int k = 0; k <= 5; k++) cnt += (s[i + k][j] == '#');
		if(cnt >= 4) { puts("Yes"); return 0; }
	}
	for(int i = 1; i <= n - 5; i++) for(int j = 1; j <= n - 5; j++) {
		int cnt = 0;
		for(int k = 0; k <= 5; k++) cnt += (s[i + k][j + k] == '#');
		if(cnt >= 4) { puts("Yes"); return 0; }
	}
	for(int i = 1; i <= n - 5; i++) for(int j = 6; j <= n; j++) {
		int cnt = 0;
		for(int k = 0; k <= 5; k++) cnt += (s[i + k][j - k] == '#');
		if(cnt >= 4) { puts("Yes"); return 0; }
	}
	puts("No");
	return 0;
} /*
6
.....#
....#.
...#..
..#...
.#....
#.....
*/