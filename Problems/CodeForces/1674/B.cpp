#include <cstdio>

int order[30][30];

int main() {
	int T; scanf("%d", &T);
	int cnt = 0;
	for(int i = 0; i < 26; i++) for(int j = 0; j < 26; j++) if(i != j) order[i][j] = ++cnt;
	while(T--) {
		char s[10];
		scanf("%s", s);
		int x = s[0] - 'a', y = s[1] - 'a';
		printf("%d\n", order[x][y]);
	}
	return 0;
}