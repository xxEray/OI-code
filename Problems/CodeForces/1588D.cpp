#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 10 + 3;
const int CS = 52;
const int LEN = 120 + 5;

const char *char_of = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char str[N][LEN];
int len[N], f[1 << N][CS + 3], last[1 << N][CS + 3][2];
int pos[N][CS + 3][2], cnt[CS + 3];
int n;

void print(int s, int c) {
	if(s == -1) return;
	print(last[s][c][0], last[s][c][1]);
	putchar(char_of[c]);
}

int dfs(int s, int c1) {
	if(f[s][c1]) return f[s][c1];
	bool flg = true;
	for(int i = 1; i <= n; i++) if(!pos[i][c1][s >> (i - 1) & 1]) flg = false;
	if(flg) f[s][c1] = 1;
	for(int c2 = 0; c2 < CS; c2++) {
		int t = 0;
		flg = false;
		for(int i = 1; i <= n; i++)
			if(pos[i][c2][1] && pos[i][c1][s >> (i - 1) & 1] > pos[i][c2][1]) t |= 1 << (i - 1); 
			else if(pos[i][c2][0] && pos[i][c1][s >> (i - 1) & 1] > pos[i][c2][0]) t |= 0 << (i - 1);
			else { flg = true; break; }
		if(flg) continue;
		dfs(t, c2);
		if(f[t][c2] + 1 > f[s][c1]) f[s][c1] = f[t][c2] + 1, last[s][c1][0] = t, last[s][c1][1] = c2; // , printf("f[%d][%c] <- f[%d][%c]\n", s, char_of[c1], t, char_of[c2]);
	}
	return f[s][c1];
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(f, 0, sizeof(f));
		memset(pos, 0, sizeof(pos));
		memset(last, -1, sizeof(last));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%s", str[i] + 1), len[i] = strlen(str[i] + 1);
		for(int i = 1; i <= n; i++) for(int j = 1; j <= len[i]; j++)
			if('a' <= str[i][j] && str[i][j] <= 'z') str[i][j] -= 'a';
			else str[i][j] += -'A' + 26;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < CS; j++) cnt[j] = 0;
			for(int j = 1; j <= len[i]; j++) pos[i][str[i][j]][cnt[str[i][j]]++] = j;
		}
		int U = (1 << n) - 1;
		int ans = 0, ansid[2] = {};
		for(int s = 0; s <= U; s++)
			for(int c = 0; c < CS; c++) {
				dfs(s, c);
				if(f[s][c] > ans) ans = f[s][c], ansid[0] = s, ansid[1] = c;
				// f[s][c] && printf("f[%d][%c] = %d\n", s, char_of[c], f[s][c]);
			}
		printf("%d\n", ans);
		if(ans) print(ansid[0], ansid[1]);
		puts("");
	}
	return 0;
} /*
1
3
azAZ
aAzZ
aazz
*/