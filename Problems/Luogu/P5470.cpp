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
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K, L;
int a[N], b[N];

int ca[N], cb[N];
struct cmpA { bool operator()(int x, int y) const { return std::make_pair(a[x], x) < std::make_pair(a[y], y); } };
struct cmpB { bool operator()(int x, int y) const { return std::make_pair(b[x], x) < std::make_pair(b[y], y); } };
struct cmpAB { bool operator()(int x, int y) const { return std::make_pair(a[x] + b[x], x) < std::make_pair(a[y] + b[y], y); } };
std::set<int, cmpAB> st;
std::set<int, cmpA> st0l, str;
std::set<int, cmpB> st0r, stl;

int main() {
	// freopen("P5470.in", "r", stdin);
	int T; read(T);
	while(T--) {
		st.clear(), st0l.clear(), st0r.clear(), stl.clear(), str.clear();
		read(n), read(K), read(L);
		for(int i = 1; i <= n; i++) read(a[i]);
		for(int i = 1; i <= n; i++) read(b[i]);
		for(int i = 1; i <= n; i++) {
			st0l.emplace(i), st0r.emplace(i);
			st.emplace(i);
			ca[i] = cb[i] = 0;
		}
		LL ans = 0;
		int cnt0 = K - L, cnt1 = L;
		// printf("ca: "); for(int i = 1; i <= n; i++) printf("%d ", ca[i]); puts("");
		// printf("cb: "); for(int i = 1; i <= n; i++) printf("%d ", cb[i]); puts("");
		// printf("cnt0 = %d, cnt1 = %d\n", cnt0, cnt1);
		// for(int i = 1; i <= n; i++) if(!ca[i] && !cb[i]) st.emplace(a[i] + b[i], i);
		// for(int i = 1; i <= n; i++) if(ca[i] && !cb[i]) stl.emplace(b[i], i);
		// for(int i = 1; i <= n; i++) if(cb[i] && !ca[i]) str.emplace(a[i], i);
		while(cnt0 || cnt1) {
			if(cnt0) {
				cnt0--;
				int p = *st0l.rbegin(), q = *st0r.rbegin();
				// printf("type 0: p = %d, q = %d\n", p, q);
				st0l.erase(--st0l.end()), st0r.erase(--st0r.end());
				ca[p] = cb[q] = 1;
				st.erase(p), st.erase(q);
				str.erase(p), stl.erase(q);
				if(!cb[p]) stl.emplace(p);
				if(!ca[q]) str.emplace(q);
				if(cb[p]) cnt0++, cnt1--;
				if(ca[q]) cnt0++, cnt1--;
				if(p == q) cnt0--, cnt1++;
				if(cnt1 < 0) cnt0 += cnt1, cnt1 = 0;
				continue;
			}
			cnt1--;
			int v0 = st.empty() ? -INF : a[*st.rbegin()] + b[*st.rbegin()];
			int v1 = (st0l.empty() ? -INF : a[*st0l.rbegin()]) + (stl.empty() ? -INF : b[*stl.rbegin()]);
			int v2 = (st0r.empty() ? -INF : b[*st0r.rbegin()]) + (str.empty() ? -INF : a[*str.rbegin()]);
			int v = std::max({v0, v1, v2});
			if(v == v0) {
				int p = *st.rbegin();
				st.erase(--st.end());
				ca[p] = cb[p] = 1;
				st0l.erase(p), st0r.erase(p);
				// printf("v0: p = %d\n", p);
			} else if(v == v1) {
				int p = *st0l.rbegin(), q = *stl.rbegin();
				st0l.erase(--st0l.end()), stl.erase(--stl.end());
				// printf("v1: p = %d, q = %d\n", p, q);
				ca[p] = cb[q] = 1;
				if(cb[p]) str.erase(p), cnt1--, cnt0++;
				st0r.erase(q);
				st.erase(p);
				if(!cb[p]) stl.emplace(p);
			} else {
				int p = *st0r.rbegin(), q = *str.rbegin();
				st0r.erase(--st0r.end()), str.erase(--str.end());
				cb[p] = ca[q] = 1;
				if(ca[p]) stl.erase(p), cnt1--, cnt0++;
				st0l.erase(q);
				// printf("v2: p = %d, q = %d\n", p, q);
				st.erase(p);
				if(!ca[p]) str.emplace(p);
			}
			if(cnt1 < 0) cnt0 += cnt1, cnt1 = 0;
		}
		// printf("ca: "); for(int i = 1; i <= n; i++) printf("%d ", ca[i]); puts("");
		// printf("cb: "); for(int i = 1; i <= n; i++) printf("%d ", cb[i]); puts("");
		for(int i = 1; i <= n; i++) if(ca[i]) ans += a[i];
		for(int i = 1; i <= n; i++) if(cb[i]) ans += b[i];
		write(ans, '\n');
	}
	return 0;
} /*
1
10 5 3
735084174 488913175 91064565 53816995 574285514 475473599 708948816 889950656 778224399 737950077
160320759 465716661 532460299 5198228 873700500 372678168 623759708 781673836 420156941 264848092

7081909406
*/