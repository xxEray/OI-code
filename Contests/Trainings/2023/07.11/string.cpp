#include <bits/stdc++.h>

const int N = 2e6 + 5;

int n;
char s[N];

bool eqp[N], eqs[N];

int main() {
#ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	scanf("%d%s", &n, s + 1);
	if(~n & 1) { puts("NOT POSSIBLE"); return 0; }
	eqp[0] = eqs[0] = true;
	for(int i = 1; i <= n / 2; i++) eqp[i] = (eqp[i - 1] && s[i] == s[n / 2 + 1 + i]);
	for(int i = 1; i <= n / 2; i++) eqs[i] = (eqs[i - 1] && s[n / 2 + 1 - i + 1] == s[n - i + 1]);
	bool flagr = false;
	for(int i = 0; i <= n / 2; i++) flagr |= (eqp[i] && eqs[n / 2 - i]);
	eqp[0] = eqs[0] = true;
	for(int i = 1; i <= n / 2; i++) eqp[i] = (eqp[i - 1] && s[n / 2 + i] == s[i]);
	for(int i = 1; i <= n / 2; i++) eqs[i] = (eqs[i - 1] && s[n - i + 1] == s[n / 2 + 1 - i]);
	bool flagl = false;
	for(int i = 0; i <= n / 2; i++) flagl |= (eqp[i] && eqs[n / 2 - i]);
	if(!flagl && !flagr) printf("NOT POSSIBLE");
	else if(flagl && flagr) {
		bool eq = true;
		for(int i = 1; i <= n / 2; i++) eq &= (s[i] == s[n / 2 + 1 + i]);
		if(eq) for(int i = 1; i <= n / 2; i++) putchar(s[i]);
		else printf("NOT UNIQUE");
	} else {
		if(flagl) for(int i = 1; i <= n / 2; i++) putchar(s[i]);
		else for(int i = n / 2 + 2; i <= n; i++) putchar(s[i]);
	}
	puts("");
	return 0;
}