#include <bits/stdc++.h>

const int N = 30 + 5;

int n, m, Q;
char s[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	scanf("%d", &Q);
	while(Q--) {
		int x = 1, y;
		scanf("%d", &y);
		while(true) {
			if(x == n || s[x + 1][y] == 'X') break;
			else if(s[x + 1][y] == '.') x++;
			else if(s[x + 1][y] == 'O' && s[x][y - 1] == '.' && s[x + 1][y - 1] == '.') x++, y--;
			else if(s[x + 1][y] == 'O' && s[x][y + 1] == '.' && s[x + 1][y + 1] == '.') x++, y++;
			else break;
		}
		s[x][y] = 'O';
	}
	for(int i = 1; i <= n; i++) printf("%s\n", s[i] + 1);
	return 0;
}
