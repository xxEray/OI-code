#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 20 + 5;
const int INF = 0x3f3f3f3f;

LL n, mod;

LL ans;
char s[N];

int ind;
std::pair<int, int> calc() {
	int now = 0, status = 0;
	while(ind <= n) {
		if(s[ind] == '+') now++;
		else if(s[ind] == '-') now--;
		else if(s[ind] == '[') {
			status = (status == 0 ? 1 : status), ind++;
			auto pr = calc();
			int x = pr.first, st = pr.second;
			if(x == 0) status = 1;
			else if(st == -1) status = -1;
			else if(st == 1 && x) status = -1;
			else if((long long)now * x >= 0 || now % x) status = -1;
			else status = 1;
			now = 0;
		} else if(s[ind] == ']') { ind++; return {now, status}; }
		ind++;
	}
	return {now, status};
}
bool check() {
	int cnt = 0;
	for(int j = 1; j <= n; j++) {
		cnt += (s[j] == '[' ? 1 : (s[j] == ']' ? -1 : 0));
		if(cnt < 0) return false;
	}
	if(cnt) return false;
	ind = 1;
	return (calc().second != -1);
}
void dfs(int i) {
	if(i == n + 1) {
		(ans += check()) %= mod;
	} else {
		s[i] = '+', dfs(i + 1);
		s[i] = '-', dfs(i + 1);
		s[i] = '[', dfs(i + 1);
		s[i] = ']', dfs(i + 1);
	}
}

int main() {
#ifndef DEBUG
	freopen("language.in", "r", stdin);
	freopen("language.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &mod);
	dfs(1);
	printf("%lld\n", ans);
	return 0;
} /*
7 10000000
output: 848
*/