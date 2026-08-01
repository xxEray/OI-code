#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <string>

const int N = 1e6 + 5;
const int MAXK = 60;

char s[N];
std::string cs;
std::vector<int> t[300];
int n, K;

int c[N][2], fail[N], end[N], tot;
char tmp[N];

void build() {
	std::queue<int> q;
	for(int i = 0; i <= 1; i++) if(c[0][i]) q.push(c[0][i]);
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		end[now] |= end[fail[now]];
		for(int j = 0; j <= 1; j++)
			if(c[now][j]) fail[c[now][j]] = c[fail[now]][j], q.push(c[now][j]);
			else c[now][j] = c[fail[now]][j];
	}
}

int main() {
	scanf("%d%s", &K, s);
	n = strlen(s);
	for(int i = 1, ch = 'A' - 1; i <= K; i++) ch = (ch == 'Z' ? 'a' : ch + 1), cs.push_back(ch);
	int flag = 0;
	for(char ch : cs) {
		scanf("%s", tmp);
		int len = strlen(tmp);
		for(int j = 0; j < len; j++) t[ch].push_back(tmp[j] - '0');
		if(t[ch].size() == 1U) flag |= (t[ch][0] + 1);
	}
	if(flag == 3) { puts("-1"); return 0; }
	if(flag == 0) {
		int ans = 0;
		for(int i = 0; i < n; i++) ans += t[s[i]].size();
		printf("%d\n", ans);
		return 0;
	}
	if(flag == 2) for(char ch : cs) for(int &j : t[ch]) j ^= 1;
	// printf("s: "); for(int x : a) printf("%d", x); puts("");
	// for(char ch : cs) {
	// 	printf("t[%c]: ", ch);
	// 	for(int j : t[ch]) printf("%d", j);
	// 	puts("");
	// }
	for(char ch : cs) {
		int now = 0;
		for(int j = (int)t[ch].size() - 1; j >= 0; j--) {
			if(!c[now][t[ch][j]]) c[now][t[ch][j]] = ++tot;
			now = c[now][t[ch][j]];
		}
		end[now] = 1;
	}
	build();
	int now = 0, ans = 1;
	flag = 1;
	for(int i = n - 1; i >= 0; i--)
		for(int j = (int)t[s[i]].size() - 1; j >= 0; j--) {
			int ch = t[s[i]][j];
			now = c[now][ch];
			if(!flag) ans += (ch == 1);
			if(!end[now]) flag = 0;
		}
	if(flag) { puts("-1"); return 0; }
	printf("%d\n", ans);
	return 0;
}