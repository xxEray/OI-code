/*
abaaba 1:2
abaababaab 2:3
abaababaabaababa 3:5
abaababaabaababaababaabaab 5:8
abaababaabaababaababaabaababaabaababaababa 8:13
abaababaabaababaababaabaababaabaababaababaabaababaababaabaababaabaab

f_i < t <= 2f_i
f_i < t
f_i >= t/2
*/

#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const LL MOD = 998244353;
const int N = 1e5 + 5;

char s[N];
int n, Q;

int nxt[N];
LL suma, sumb;
LL pre[N];

LL fib[N];
int cfib = 2;
int la, lb;

void clear() {
	for(int i = 1; i <= n; i++) nxt[i] = pre[i] = 0;
}

int main() {
	int T; scanf("%d", &T);
	fib[0] = 3, fib[1] = 5;
	while(true) {
		fib[cfib] = fib[cfib - 1] + fib[cfib - 2];
		if(fib[cfib] >= (LL)(1e18)) break;
	}
	printf("%d\n", cfib);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		clear();
		for(int i = 1, j = 0; i <= n; i++) {
			while(j && s[i] != s[j + 1]) j = nxt[j];
			if(s[i] == s[j + 1]) j++;
			nxt[i] = j;
		}
		la = nxt[n / 2], lb = n / 2 - la;
		for(int i = 1; i <= la; i++) (suma += s[i] - '0') %= MOD;
		for(int i = 1; i <= n; i++) 
		scanf("%*d%d", &Q);
		while(Q--) {
			
		}
	}
	return 0;
} /*
2
121121
15 2
4 10
1 15
1111
10 2
1 5
1 10
output:
1212112
230884310
11111
112866758
*/