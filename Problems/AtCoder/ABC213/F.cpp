#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long LL;

const int N = 1e6 + 5;

char s[N];
int n, m;

int sa[N], rk[N], tot[N], ht[N], tp[N];
void SA() {
	m = 'z';
	for(int i = 0, p = 0; i <= n && p < n; i = (i ? i << 1 : 1), m = p) {
		if(i) {
			p = 0;
			for(int j = 1; j <= i; j++) tp[++p] = n - j + 1;
			for(int j = 1; j <= n; j++) if(sa[j] > i) tp[++p] = sa[j] - i;
		} else for(int j = 1; j <= n; j++) rk[j] = s[j], tp[j] = j;
		for(int j = 0; j <= m; j++) tot[j] = 0;
		for(int j = 1; j <= n; j++) tot[rk[j]]++;
		for(int j = 1; j <= m; j++) tot[j] += tot[j - 1];
		for(int j = n; j >= 1; j--) sa[tot[rk[tp[j]]]--] = tp[j];
		for(int j = 1; j <= n; j++) tp[j] = rk[j];
		rk[sa[1]] = p = 1;
		for(int j = 2; j <= n; j++)
			rk[sa[j]] = (tp[sa[j - 1]] == tp[sa[j]] && tp[sa[j - 1] + i] == tp[sa[j] + i] ? p : ++p);
	}
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i++) {
		if(rk[i] == 1) { ht[rk[i]] = 0; continue; }
		if(k) k--;
		int j = sa[rk[i] - 1];
		while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}

std::vector<int> q;
LL out[N];

int main() {
	scanf("%d%s", &n, s + 1);
	SA();
	LL ans = 0;
	#define last(x) ((x).size() == 1u ? 0 : (x)[(int)(x).size() - 2])
	for(int i = 1; i <= n; i++) {
		while(!q.empty() && ht[q.back()] >= ht[i]) ans -= (LL)(q.back() - last(q)) * ht[q.back()], q.pop_back();
		q.push_back(i), ans += (LL)(i - last(q)) * ht[i];
		out[sa[i]] += ans;
	}
	#undef last
	ans = 0, q.clear();
	#define last(x) ((x).size() == 1u ? n + 1 : (x)[(int)(x).size() - 2])
	for(int i = n; i >= 1; i--) {
		while(!q.empty() && ht[q.back()] >= ht[i]) ans -= (LL)(last(q) - q.back()) * ht[q.back()], q.pop_back();
		q.push_back(i), ans += (LL)(last(q) - i) * ht[i];
		out[sa[i - 1]] += ans;
	}
	#undef last
	for(int i = 1; i <= n; i++) printf("%lld\n", out[i] + n - i + 1);
	return 0;
}