#include <cstdio>
#include <algorithm>
#include <vector>

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

const int N = 2500 + 5;

int n, m;
int a[N][N];

int son[N][2], fa[N];
bool msk[N][N];
std::vector<int> common[N][N];
std::vector<int> st[N][N];
void calc(const int &row, int x, int l, int r, const bool &type) {
	if(l > r) return;
	calc(row, son[x][0], l, x - 1, type), calc(row, son[x][1], x + 1, r, type);
	if(type) {
		for(int v : st[row][x])
			if((!son[x][0] || msk[son[x][0]][v]) && (!son[x][1] || msk[son[x][1]][v]))
				msk[x][v] = true, common[l][r].push_back(v);
	} else {
		for(int v : st[row][x]) msk[x][v] = false;
		common[l][r].clear();
	}
}

int l[N], r[N], ll[N], lr[N];
int q[N], top;
int f[N][N];

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) read(a[i][j]);
	int ans = 0;
	for(int j = 1; j <= m; j++) {
		top = 0;
		for(int i = 1; i <= n; i++) {
			while(top && a[q[top]][j] <= a[i][j]) top--;
			l[i] = top ? q[top] + 1 : 0;
			q[++top] = i;
		}
		top = 0;
		for(int i = n; i >= 1; i--) {
			while(top && a[q[top]][j] <= a[i][j]) top--;
			r[i] = top ? q[top] - 1 : 0;
			q[++top] = i;
		}
		for(int i = 1; i <= n; i++) if(l[i] && r[i]) {
			if(f[l[i]][r[i]]) l[i] = r[i] = 0;
			else f[l[i]][r[i]] = true;
		}
		for(int i = 1; i <= n; i++) if(l[i] && r[i]) st[r[i]][j].push_back(l[i]);
		for(int i = 1; i <= n; i++) if(l[i] && r[i]) f[l[i]][r[i]] = false;
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!st[i][j].empty()) {
	// 	printf("st[%d][%d]: ", i, j);
	// 	for(int v : st[i][j]) printf("%d ", v);
	// 	puts("");
	// }
	for(int j = 1; j <= m; j++) l[j] = r[j] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) ll[j] = l[j], lr[j] = r[j];
		top = 0;
		for(int j = 1; j <= m; j++) {
			while(top && a[i][q[top]] <= a[i][j]) top--;
			l[j] = top ? q[top] + 1 : 0;
			q[++top] = j;
		}
		top = 0;
		for(int j = m; j >= 1; j--) {
			while(top && a[i][q[top]] <= a[i][j]) top--;
			r[j] = top ? q[top] - 1 : 0;
			q[++top] = j;
		}
		for(int j = 1; j <= m; j++) if(ll[j] && lr[j]) f[ll[j]][lr[j]] *= -1;
		for(int j = 1; j <= m; j++) if(l[j] && r[j]) {
			if(f[l[j]][r[j]] > 0) l[j] = r[j] = 0;
			else f[l[j]][r[j]] = -f[l[j]][r[j]] + 1;
		}
		for(int j = 1; j <= m; j++) if(ll[j] && lr[j] && f[ll[j]][lr[j]] < 0) f[ll[j]][lr[j]] = 0;
		// for(int j = 1; j <= m; j++) if(l[j] && r[j]) printf("%d: [%d, %d] for %d..%d rows\n", i, l[j], r[j], i - f[l[j]][r[j]] + 1, i);
		for(int j = 1; j <= m; j++) son[j][0] = son[j][1] = fa[j] = 0;
		std::vector<int> stk;
		for(int j = 1; j <= m; j++) {
			int last = 0;
			while(!stk.empty() && a[i][stk.back()] < a[i][j]) last = stk.back(), stk.pop_back();
			int ff = stk.empty() ? 0 : stk.back();
			fa[j] = ff, son[j][0] = last, fa[son[j][0]] = j, ff ? son[ff][1] = j : 0;
			stk.push_back(j);
		}
		// printf("%d:\n", i);
		// for(int j = 1; j <= m; j++) printf("  %d: fa=%d, son=%d,%d\n", j, fa[j], son[j][0], son[j][1]);
		int high = 0;
		for(int j = 1; j <= m; j++) if(!fa[j]) high = j;
		calc(i, high, 1, m, true);
		for(int j = 1; j <= m; j++) if(l[j] && r[j])
			for(int v : common[l[j]][r[j]])
				ans += (v >= i - f[l[j]][r[j]] + 1);
		calc(i, high, 1, m, false);
	}
	write(ans, '\n');
	return 0;
} /*
5 5
4 4 4 4 4
4 3 3 3 4
4 3 2 3 4
4 3 3 3 4
4 4 4 4 4
*/