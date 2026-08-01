#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n;
char tmp[N];
std::string s[N];

struct PAM {
	int fail[N], len[N], nxt[N][26];
	int last, tot;
	PAM() : last(1), tot(1) { len[0] = -1, len[1] = 0; fail[1] = 0; }
	int sid;
	void new_string(int strid) {
		sid = strid;
		last = 1;
	}
	void insert(int id) {
		char c = s[sid][id] - 'a';
		int now = last;
		while(s[sid][id - len[now] - 1] != s[sid][id]) now = fail[now];
		if(!nxt[now][c]) nxt[now][c] = ++tot, len[nxt[now][c]] = len[now] + 2;
		last = nxt[now][c];
		if(now == 0) { fail[last] = 1; return; }
		now = fail[now];
		while(s[sid][id - len[now] - 1] != s[sid][id]) now = fail[now];
		fail[last] = nxt[now][c];
	}
} pam;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", tmp), s[i] = tmp;
	for(int i = 1; i <= n; i++) {
		pam.new_string(i);
		for(int j = 0; j < (int)s[i].size(); j++) pam.insert(j);
	}
	// for(int i = 0; i <= pam.tot; i++) printf("%d: len=%d, fail=%d, nxt['a']=%d\n", i, pam.len[i], pam.fail[i], pam.nxt[i][0]);
	LL ans = 0;
	for(int i = 2; i <= pam.tot; i++)
		if(pam.len[i] % (pam.len[i] - pam.len[pam.fail[i]]) == 0) {
			// printf("%d - %d\n", pam.len[i], pam.len[i] - pam.len[pam.fail[i]]);
			(ans += pam.len[i] / (pam.len[i] - pam.len[pam.fail[i]]) * 2 - 1);
		} else {
			// printf("single %d\n", pam.len[i]);
			ans++;
		}
	printf("%lld\n", ans);
	return 0;
} /*
3
abaaa
abbbba
bbbaba

1
aba
*/