#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 2e5 + 5;

int n;
LL K;
char s[N], t[2 * N], r[3 * N];

bool flag;
void set(int i, char c) {
	if(t[i] == 0) t[i] = c;
	else if(t[i] != c) flag = false;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &K);
		scanf("%s", s + 1);
		flag = true;
		if(K / (2 * n) % 2 == 1) std::reverse(s + 1, s + n + 1);
		K %= 2 * n;
		if(K == 0) K += 2 * n, std::reverse(s + 1, s + n + 1);
		for(int i = 1; i <= K; i++) t[i] = 0;
		for(int i = 1; i <= n; i++) if(K - i + 1 >= 1) set(K - i + 1, s[i]);
		for(int i = 1; i <= n; i++) if(n - i + 1 <= K) set(n - i + 1, s[i]);
		for(int i = 1; i <= n; i++) r[i] = s[i];
		for(int i = 1; i <= K; i++) r[n + i] = t[i];
		for(int i = 1; i <= n + K; i++) flag &= r[i] == r[1 + n + K - i];
		for(int i = 1; i <= K; i++) r[i] = t[i];
		for(int i = 1; i <= n; i++) r[K + i] = s[i];
		for(int i = 1; i <= n + K; i++) flag &= r[i] == r[1 + n + K - i];
		puts(flag ? "Yes" : "No");
	}
	return 0;
} /*
ab.ba
ba.ab
*/