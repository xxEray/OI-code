#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

const int N = 100 + 5;
const int CS = 300 + 5;
const int MOD = 998244353;

std::string cs;
char s[N][N];
int ls[N];
int n, m, ccs;

int c[N * N][CS], fail[N * N], end[N * N];
int tot;

int f[2][N * N];

void build() {
	std::queue<int> q;
	for(char ch : cs) if(c[0][ch]) q.push(c[0][ch]);
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		// end[now] |= end[fail[now]];
		for(char ch : cs)
			if(c[now][ch]) fail[c[now][ch]] = c[fail[now]][ch], q.push(c[now][ch]);
			else c[now][ch] = c[fail[now]][ch];
	}
}

int main() {
	// freopen("sky.in", "r", stdin);
	// freopen("sky.out", "w", stdout);
	scanf("%d%d%d", &ccs, &n, &m);
	scanf("%s", s[0]), cs = s[0], s[0][0] = '\0';
	for(int i = 1; i <= m; i++) scanf("%s", s[i] + 1), ls[i] = strlen(s[i] + 1);
	for(int i = 1; i <= m; i++) {
		int now = 0;
		for(int j = 1; j <= ls[i]; j++) {
			if(c[now][s[i][j]] == 0) c[now][s[i][j]] = ++tot;
			now = c[now][s[i][j]];
		}
		end[now]++;
	}
	build();
	f[0][0] = 1;
	// for(int i = 0; i <= tot; i++) printf("end[%d] = %d\n", i, end[i]);
	for(int i = 0, t = i & 1; i < n; i++, t ^= 1) {
		for(int j = 0; j <= tot; j++) f[t ^ 1][j] = 0;
		for(int j = 0; j <= tot; j++)
			for(char ch : cs)
				if(!end[c[j][ch]]) (f[t ^ 1][c[j][ch]] += f[t][j]) %= MOD;
	}
	int ans = 0;
	for(int i = 0; i <= tot; i++) (ans += f[n & 1][i]) %= MOD;
	printf("%d\n", ans);
	return 0;
} /*
2 2 1
ab
ab
*/