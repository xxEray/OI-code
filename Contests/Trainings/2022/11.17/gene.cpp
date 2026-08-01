#include <bits/stdc++.h>

typedef unsigned long long LL;

const int N = 1e5 + 5;
const LL HSH = 137;

int n;
char s[N], t[N];
LL power[N], hs[N], ht[N];
int cnt[N][100];

int L;

bool equal(int r, int i, int j) {
	LL hi = (L + r - 1 > i) * (hs[L + r - 1] - hs[i] * power[L + r - 1 - i]) + (ht[n - std::max(L, i - r + 1) + 1] - ht[n - i] * power[i - std::max(L, i - r + 1) + 1]) * (L + r - 1 > i ? power[L + r - 1 - i] : 1);
	LL hj = (L + r - 1 > j) * (hs[L + r - 1] - hs[j] * power[L + r - 1 - j]) + (ht[n - std::max(L, j - r + 1) + 1] - ht[n - j] * power[j - std::max(L, j - r + 1) + 1]) * (L + r - 1 > j ? power[L + r - 1 - j] : 1);
	return hi == hj;
}
int compare(int i, int j) {
	int l = 1, r = n - L + 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(equal(mid, i, j)) l = mid + 1;
		else r = mid;
	}
	char c1 = (L + l - 1 <= i ? t[n - (i - l + 1) + 1] : s[L + l - 1]);
	char c2 = (L + l - 1 <= j ? t[n - (j - l + 1) + 1] : s[L + l - 1]);
	return c1 == c2 ? 0 : (c1 < c2 ? -1 : 1);
}
void solve() {
	int r = L;
	for(int i = L + 1; i <= n; i++) if(compare(r, i) == 1) r = i;
	for(int i = 1; i < L; i++) putchar(s[i]);
	for(int i = r; i >= L; i--) putchar(t[n - i + 1]);
	for(int i = r + 1; i <= n; i++) putchar(s[i]);
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) t[i] = s[i];
	std::reverse(t + 1, t + n + 1);
	for(int i = 1; i <= n; i++) t[i] = (t[i] == 'A' || t[i] == 'T') ? (t[i] == 'A' ? 'T' : 'A') : (t[i] == 'C' ? 'G' : 'C');
	power[0] = 1;
	for(int i = 1; i <= n; i++) {
		hs[i] = hs[i - 1] * HSH + s[i];
		ht[i] = ht[i - 1] * HSH + t[i];
		power[i] = power[i - 1] * HSH;
	}
	for(int i = n; i >= 1; i--) {
		cnt[i]['A'] = cnt[i + 1]['A'], cnt[i]['C'] = cnt[i + 1]['C'], cnt[i]['G'] = cnt[i + 1]['G'], cnt[i]['T'] = cnt[i + 1]['T'];
		cnt[i][s[i]]++;
	}
	for(int i = 1; i <= n; i++) {
		if(s[i] > 'A' && cnt[i]['T']) { L = i; break; }
		if(s[i] > 'C' && cnt[i]['G']) { L = i; break; }
		if(s[i] > 'G' && cnt[i]['C']) { L = i; break; }
		if(s[i] > 'T' && cnt[i]['A']) { L = i; break; }
	}
	if(L == 0) L = n;
	solve();
	return 0;
}