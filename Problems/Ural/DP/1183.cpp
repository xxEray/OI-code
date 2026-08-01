#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

char s[N];
int n;

int f[N][N], pre[N][N];

inline void printstrs(char a) { printf("%s", (a == '(' || a == ')' ? "()" : "[]")); }
inline bool couple(char a, char b) { return (a == '(' && b == ')') || (a == '[' && b == ']'); }

void print(int l, int r) {
	if(l > r) return;
	else if(pre[l][r] == -1) printstrs(s[l]);
	else if(pre[l][r] == -2) printf("%c%c", s[l], s[r]);
	else if(pre[l][r] == 0) putchar(s[l]), print(l + 1, r - 1), putchar(s[r]);
	else print(l, pre[l][r]), print(pre[l][r] + 1, r);
}

int main() {
	scanf("%s", s + 1);
	n = std::strlen(s + 1);
	for(int len = 1; len <= n; len++)
		for(int l = 1; l <= n; l++) {
			int r = l + len - 1;
			f[l][r] = INF;
			if(l == r) { pre[l][r] = -1; f[l][r] = 1; continue; }
			for(int k = l; k < r; k++)
				if(f[l][r] > f[l][k] + f[k + 1][r])
					f[l][r] = f[l][k] + f[k + 1][r], pre[l][r] = k;
			if(couple(s[l], s[r])) {
				if(r - l == 1) f[l][r] = 0, pre[l][r] = -2;
				else if(f[l][r] > f[l + 1][r - 1]) f[l][r] = f[l + 1][r - 1], pre[l][r] = 0;
			}
		}
	print(1, n);
	return 0;
}