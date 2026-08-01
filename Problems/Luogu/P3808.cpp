#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N = 1e6 + 5;
const int M = 26 + 3;

char s[N];
int n;

struct ACautomaton {
	int c[N][M], fail[N], cnt[N];
	int tot;
	ACautomaton() { init(); }
	void init() {
		memset(c, 0, sizeof(c));
		memset(fail, 0, sizeof(fail));
		memset(cnt, 0, sizeof(cnt));
		tot = 0;
	}
	void insert(const char *s) {
		int len = strlen(s + 1);
		int now = 0;
		for(int i = 1; i <= len; i++) {
			int ch = s[i] - 'a';
			if(!c[now][ch]) c[now][ch] = ++tot;
			now = c[now][ch];
		}
		cnt[now]++;
	}
	void build() {
		std::queue<int> q;
		for(int i = 0; i < 26; i++) if(c[0][i]) q.push(c[0][i]);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = 0; i < 26; i++)
				if(c[u][i]) fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
				else c[u][i] = c[fail[u]][i];
		}
	}
	int match(const char *t) {
		int ret = 0, now = 0, len = strlen(t + 1);
		for(int i = 1; i <= len; i++) {
			int ch = t[i] - 'a';
			now = c[now][ch];
			for(int j = now; j && cnt[j] != -1; j = fail[j]) ret += cnt[j], cnt[j] = -1;
		}
		return ret;
	}
} ac;

int main() {
	// freopen("D:\\Useless\\Temp\\P3808_2.in", "r", stdin);
	ac.init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", s + 1), ac.insert(s);
	ac.build();
	scanf("%s", s + 1);
	printf("%d\n", ac.match(s));
	return 0;
}