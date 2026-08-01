#include <cstdio>
#include <algorithm>
#include <bitset>

const int N = 5000 + 5;

std::bitset<N> a[N];
int n;

inline char nc(){
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline int readint(){
    char ch = nc(); int sum = 0;
    while(!(ch >= '0' && ch <= '9')) ch = nc();
    while(ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = nc();
    return sum;
}

int main() {
// #ifndef DEBUG
	// freopen("discuss.in", "r", stdin);
	// freopen("discuss.out", "w", stdout);
// #endif
	int T; T = readint();
	while(T--) {
		n = readint();
		for(int i = 1; i <= n; i++) {
			a[i].reset();
			int c;
			c = readint();
			while(c--) a[i][readint()] = 1;
		}
		int ansi = 0, ansj = 0;
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++)
			if(((a[i] & a[j]) != 0) && ((a[i] & a[j]) != a[i]) && ((a[i] & a[j]) != a[j])) { ansi = i, ansj = j; break; }
		if(ansi) printf("YES\n%d %d\n", ansi, ansj);
		else puts("NO");
	}
	return 0;
}