#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

const int N = 2e5 + 5;

char s[N];
int n;

int sum[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		int cnt = 0, c = 0;
		for(int i = 1; i <= n; i++) cnt += s[i] == '?', c += (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0));
		assert((cnt + c) % 2 == 0);
		int tot = (cnt - c) / 2;
		if(tot == cnt) { puts("YES"); continue; }
		int ind = -1;
		for(int i = 1; i <= n; i++) {
			sum[i] = sum[i - 1] + (s[i] == ')' ? -1 : 1);
			if(s[i] == '?') {
				if(tot == 0) { ind = i; break; }
				tot--;
			}
		}
		assert(ind != -1);
		// for(int i = 1; i < ind; i++) printf("%d ", sum[i]);
		// puts("");
		for(int i = ind - 2; i >= 1; i--) sum[i] = std::min(sum[i], sum[i + 1]);
		bool flag = true;
		for(int i = 1; i <= ind - 1; i++) if(s[i] == '?') flag &= sum[i] <= 1;
		puts(flag ? "YES" : "NO");
	}
	return 0;
} /*
1
(?)(?)
*/