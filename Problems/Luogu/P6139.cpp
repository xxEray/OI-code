#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
char s[N];

std::map<char, int> c[N * 2];
int link[N * 2], len[N * 2];
int last, cnt = 1;
void insert(char ch) {
	if(c[last][ch]) {
		int p = last, q = c[p][ch];
		if(len[q] == len[p] + 1) { last = q; return; }
		int clone = ++cnt;
		last = clone;
		len[clone] = len[p] + 1;
		link[clone] = link[q], link[q] = clone;
		c[clone] = c[q];
		for(; p && c[p][ch] == q; p = link[p]) c[p][ch] = clone;
	} else {
		int cur = ++cnt, p = last;
		len[cur] = len[last] + 1, last = cur;
		for(; p && !c[p][ch]; p = link[p]) c[p][ch] = cur;
		if(!p) { link[cur] = 1; return; }
		int q = c[p][ch];
		if(len[q] == len[p] + 1) { link[cur] = q; return; }
		int clone = ++cnt;
		len[clone] = len[p] + 1;
		link[clone] = link[q], link[q] = clone;
		c[clone] = c[q];
		link[cur] = clone;
		for(; p && c[p][ch] == q; p = link[p]) c[p][ch] = clone;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		int cn = strlen(s + 1);
		last = 1;
		for(int j = 1; j <= cn; j++) insert(s[j]);
	}
	long long ans = 0;
	for(int i = 1; i <= cnt; i++) ans += len[i] - len[link[i]];
	printf("%lld\n%d\n", ans, cnt);
	return 0;
}