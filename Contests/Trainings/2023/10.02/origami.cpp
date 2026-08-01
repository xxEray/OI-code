#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::rdc;
using FIO::read;

typedef long long LL;

const int N = 1e6 + 5;
const unsigned long long HSH = 233;

int n, m;
std::vector<char> s[N];

unsigned long long hshp[N], hshq[N];
int p[2 * N], q[2 * N];
int asp[2 * N], asq[2 * N];

void manacher(int len, int *arr, int *asr, std::function<bool(int, int)> eq) {
	int r = 0, mid = 0;
	for(int i = 1; i <= len; i++) {
		if(r >= i) asr[i] = std::min(r - i, asr[2 * mid - i]);
		while(i - asr[i] - 1 >= 1 && i + asr[i] + 1 <= len && eq(arr[i - asr[i] - 1], arr[i + asr[i] + 1])) asr[i]++;
		if(r < i + asr[i]) r = i + asr[i], mid = i;
	}
}

int f[2 * N], g[2 * N], pref[2 * N], sufg[2 * N];

int main() {
	read(n), read(m);
	s[0].resize(m + 1);
	for(int i = 1, ch = rdc(); i <= n; i++) {
		s[i].resize(m + 1);
		while(ch < 'a' || ch > 'z') ch = rdc();
		for(int j = 1; j <= m; j++) s[i][j] = ch, ch = rdc();
	}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) hshp[i] = hshp[i] * HSH + s[i][j];
	for(int j = 1; j <= m; j++) for(int i = 1; i <= n; i++) hshq[j] = hshq[j] * HSH + s[i][j];
	for(int i = 1; i <= 2 * n - 1; i++) p[i] = (i & 1) ? (i + 1) / 2 : 0;
	for(int i = 1; i <= 2 * m - 1; i++) q[i] = (i & 1) ? (i + 1) / 2 : 0;
	manacher(2 * n - 1, p, asp, [&](int x, int y) -> bool { return hshp[x] == hshp[y]; });
	manacher(2 * m - 1, q, asq, [&](int x, int y) -> bool { return hshq[x] == hshq[y]; });
	LL ansp = 0, ansq = 0;
	f[0] = 1, pref[0] = pref[1] = 1;
	for(int i = 2; i <= 2 * n - 2; i += 2) {
		f[i] = (bool)(pref[i - 1] - (i - asp[i] - 2 >= 0 ? pref[i - asp[i] - 2] : 0));
		pref[i + 1] = pref[i] = f[i] + pref[i - 1];
	}
	g[2 * n] = 1, sufg[2 * n] = sufg[2 * n - 1] = 1;
	for(int i = 2 * n - 2; i >= 2; i -= 2) {
		g[i] = (bool)(sufg[i + 1] - sufg[i + asp[i] + 2]);
		sufg[i - 1] = sufg[i] = g[i] + sufg[i + 1];
	}
	for(int i = 2; i <= 2 * n; i += 2) ansp += (LL)pref[i - 1] * g[i];
	// for(int i = 2; i <= 2 * m - 2; i += 2) printf("%d: f = %d, g = %d\n", i, f[i], g[i]);
	// memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g)), memset(pref, 0, sizeof(pref)), memset(sufg, 0, sizeof(sufg));
	f[0] = 1, pref[0] = pref[1] = 1;
	for(int i = 2; i <= 2 * m - 2; i += 2) {
		f[i] = (bool)(pref[i - 1] - (i - asq[i] - 2 >= 0 ? pref[i - asq[i] - 2] : 0));
		pref[i + 1] = pref[i] = f[i] + pref[i - 1];
	}
	sufg[2 * m + 1] = 0, g[2 * m] = 1, sufg[2 * m] = sufg[2 * m - 1] = 1;
	for(int i = 2 * m - 2; i >= 2; i -= 2) {
		g[i] = (bool)(sufg[i + 1] - sufg[i + asq[i] + 2]);
		sufg[i - 1] = sufg[i] = g[i] + sufg[i + 1];
	}
	for(int i = 2; i <= 2 * m; i += 2) ansq += (LL)pref[i - 1] * g[i];
	// printf("ansp = %lld, ansq = %lld\n", ansp, ansq);
	printf("%lld\n", ansp * ansq);
	return 0;
} /*
5 7
baabbaa
cbbccbb
ababbab
cabccba
bccaacc

4 4
caaa
adaa
adaa
caaa
*/