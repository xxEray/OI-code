#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

const int N = 5e6 + 5;

int n;
int a[N];

int premn[N], sufmn[N], premx[N], sufmx[N];

bool check(int l, int r, int type) {
	// printf("check [%d, %d] (%d)\n", l, r, type);
	if(l == 0 || r == n + 1) return true;
	if(type == 0) {
		int lp = premx[l], rp = sufmx[r];
		if(a[lp] != a[rp]) return false;
		else return check(lp, rp, !type);
	} else {
		int lp = premn[l], rp = sufmn[r];
		if(a[lp] != a[rp]) return false;
		else return check(lp, rp, !type);
	}
}

int main() {
#ifndef DEBUG
	freopen("climb.in", "r", stdin);
	freopen("climb.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	premn[0] = 0, premx[0] = 0;
	for(int i = 1; i <= n + 1; i++) {
		premn[i] = (a[i] >= a[premn[i - 1]] ? premn[i - 1] : i);
		premx[i] = (a[i] <= a[premx[i - 1]] ? premx[i - 1] : i);
	}
	sufmn[n + 1] = n + 1, sufmx[n + 1] = n + 1;
	for(int i = n; i >= 0; i--) {
		sufmn[i] = (a[i] >= a[sufmn[i + 1]] ? sufmn[i + 1] : i);
		sufmx[i] = (a[i] <= a[sufmx[i + 1]] ? sufmx[i + 1] : i);
	}
	int mnlp = n + 1, mnrp = 0, mxlp = n + 1, mxrp = 0;
	for(int i = 0; i <= n + 1; i++) {
		if(a[i] == a[premn[n + 1]]) mnlp = std::min(mnlp, i), mnrp = std::max(mnrp, i);
		if(a[i] == a[premx[n + 1]]) mxlp = std::min(mxlp, i), mxrp = std::max(mxrp, i);
	}
	if(mnlp != mnrp && check(mnlp, mnrp, 0)) puts("Yes");
	else if(mxlp != mxrp && check(mxlp, mxrp, 1)) puts("Yes");
	else puts("No");
	return 0;
}