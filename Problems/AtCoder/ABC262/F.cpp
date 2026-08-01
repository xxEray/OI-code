#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N];
int n, m;

int b[N], copy[N], pos[N];
bool exist[N];

int out1[N], len1;
void solve1() {
	for(int i = 1; i <= n; i++) exist[i] = true;
	int mnid = n + 1;
	for(int i = n - m + 1; i <= n; i++) if(mnid == n + 1 || a[mnid] > a[i]) mnid = i;
	int c = 0;
	for(int i = mnid; i <= n; i++) b[++c] = a[i];
	for(int i = 1; i < mnid; i++) b[++c] = a[i];
	for(int i = 1; i <= n; i++) a[i] = b[i];
	c = n - mnid + 1;
	m -= c;
	for(int i = 1; i <= n; i++) pos[a[i]] = i;
	// for(int i = 1; i <= n; i++) if(exist[a[i]]) printf("%d ", a[i]);
	// puts("");
	int j = 1, mn = n + 1;
	for(int i = 1; i <= n; i++) {
		if(!exist[i]) continue;
		int p = pos[i];
		if(/* j < mn &&  */m >= std::max(std::min(p - c - 1, p - j), 0)) {
			while(j < p) exist[a[j]] = false, m -= (j > c), j++;
			while(j <= n && a[j] <= i) j++;
		} else mn = std::min(mn, p);
	}
	for(int i = n; i >= 1; i--) if(m && exist[a[i]]) exist[a[i]] = false, m--;
	for(int i = 1; i <= n; i++) if(exist[a[i]]) out1[++len1] = a[i];
}

int out2[N], len2;
void solve2() {
	int mnid = 0;
	for(int i = 1; i <= m + 1; i++) if(mnid == 0 || a[mnid] > a[i]) mnid = i;
	for(int i = mnid; i <= n; i++) a[i - mnid + 1] = a[i];
	int c = n - mnid + 1;
	m -= mnid - 1;
	for(int i = 1; i <= n; i++) exist[i] = false;
	for(int i = 1; i <= n; i++) pos[i] = 0;
	for(int i = 1; i <= c; i++) exist[a[i]] = true, pos[a[i]] = i;
	// printf("a: ");
	// for(int i = 1; i <= c; i++) if(exist[a[i]]) printf("%d ", a[i]);
	// puts("");
	int j = 1, mn = n + 1;
	for(int i = 1; i <= n; i++) {
		if(!exist[i]) continue;
		int p = pos[i];
		if(/* j < mn &&  */m >= p - j) {
			while(j < p) exist[a[j]] = false, m--, j++;
			while(j <= n && a[j] <= i) j++;
		} else mn = std::min(mn, p);
		// printf("%d: j = %d\n", i, j);
	}
	for(int i = c; i >= 1; i--) if(m && exist[a[i]]) exist[a[i]] = false, m--;
	for(int i = 1; i <= c; i++) if(exist[a[i]]) out2[++len2] = a[i];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) if(exist[a[i]]) printf("%d ", a[i]);
	for(int i = 1; i <= n; i++) copy[i] = a[i];
	int copym = m;
	solve1();
	m = copym;
	for(int i = 1; i <= n; i++) a[i] = copy[i];
	solve2();
	int smaller = -1;
	for(int i = 1; i <= std::min(len1, len2); i++) if(out1[i] != out2[i]) { smaller = (out1[i] < out2[i] ? 0 : 1); break; }
	if(smaller == -1) smaller = (len1 < len2 ? 0 : 1);
	// for(int i = 1; i <= len1; i++) printf("%d ", out1[i]);
	// puts("");
	// for(int i = 1; i <= len2; i++) printf("%d ", out2[i]);
	// puts("");
	if(smaller == 0) {
		for(int i = 1; i <= len1; i++) printf("%d ", out1[i]);
		puts("");
	} else {
		for(int i = 1; i <= len2; i++) printf("%d ", out2[i]);
		puts("");
	}
	return 0;
} /*
7 3
3 5 1 4 6 2 7
*/