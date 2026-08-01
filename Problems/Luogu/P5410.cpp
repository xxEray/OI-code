#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 2e7 + 5;

char a[N], b[N];

int z[N];
void z_algorithm(const char *s) { // 下标从 1 开始
	int l = 0, r = 0;
	int n = strlen(s + 1);
	for(int i = 2; i <= n; i++) {
		if(i <= r) z[i] = std::min(z[i - l + 1], r - i + 1);
		while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
		if(i + z[i] > r) l = i, r = i + z[i] - 1;
	}
}

int e[N];
void exkmp(const char *s, const char *t) { // 下标从 1 开始
	int l = 0, r = 0;
	int n = strlen(s + 1);
	for(int i = 2; i <= n; i++) {
		if(i <= r) e[i] = std::min(z[i - l + 1], r - i + 1);
		while(i + e[i] <= n && s[i + e[i]] == t[e[i] + 1]) e[i]++;
		if(i + e[i] > r) l = i, r = i + e[i] - 1;
	}
}

int main() {
	scanf("%s%s", a + 1, b + 1);
	int la = strlen(a + 1), lb = strlen(b + 1);
	z_algorithm(b);
	z[1] = lb;
	LL ans = 0;
	for(int i = 1; i <= lb; i++) ans ^= (LL)i * (z[i] + 1);
	printf("%lld\n", ans);
	exkmp(a, b);
	for(int i = 1; i <= lb; i++) if(a[i] == b[i]) e[1] = i; else break;
	ans = 0;
	for(int i = 1; i <= la; i++) ans ^= (LL)(i) * (e[i] + 1);
	printf("%lld\n", ans);
	return 0;
}