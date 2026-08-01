#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 16 + 5;

int n;
char str[N], strl[N], strr[N];

LL solve(char *s, char *t) {
	int ls = strlen(s + 1), lt = strlen(t + 1);
	LL ans = 0;
	for(int i = (s[1] == '0' ? 2 : 1); i <= lt - ls + 1; i++) {
		LL vl = 0;
		for(int j = 1; j < i; j++) vl = vl * 10 + t[j] - '0';
		int cmp = 0;
		for(int j = i; j <= i + ls - 1; j++) if(t[j] != s[j - i + 1]) { cmp = t[j] < s[j - i + 1] ? -1 : 1; break; }
		LL vr = 0, vr0 = 1;
		for(int j = i + ls; j <= lt; j++) vr = vr * 10 + t[j] - '0', vr0 *= 10;
		if(cmp == -1) ans += (vl - (s[1] == '0')) * vr0;
		else if(cmp == 0) ans += (vl - (s[1] == '0')) * vr0 + (vr + 1);
		else if(cmp == 1) ans += (vl - (s[1] == '0') + 1) * vr0;
	}
	// printf("solve %s %s = %lld\n", s + 1, t + 1, a`ns);
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s%s%s", str + 1, strl + 1, strr + 1);
		int cnt = 0;
		int ls = strlen(str + 1), lt = strlen(strl + 1);
		for(int i = 1; i <= lt - ls + 1; i++) {
			bool flag = true;
			for(int j = i; j <= i + ls - 1; j++) flag &= strl[j] == str[j - i + 1];
			cnt += flag;
		}
		// printf("cnt = %d\n", cnt);
		printf("%lld\n", solve(str, strr) - solve(str, strl) + cnt);
	}
	return 0;
} /*
1
0 1 9999999999999999
*/