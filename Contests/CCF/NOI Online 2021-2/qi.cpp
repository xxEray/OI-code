#include <cstdio>
#include <algorithm>

typedef unsigned long long ull;

const int N = 5e3 + 5;

int n, m;
ull a1, a2;

bool a[N][260];
ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}
void gen(int n, ull a1, ull a2) {
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 256; j++)
            a[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}

char s[71];
bool q[261];

int main() {
// #ifndef DEBUG
	freopen("qi.in", "r", stdin);
	freopen("qi.out", "w", stdout);
// #endif
	scanf("%d%d%llu%llu", &n, &m, &a1, &a2);
	gen(n, a1, a2);
	int lastans = 0;
	while(m--) {
		int k;
		scanf("%s%d", s, &k);
		for(int i = 0; i < 64; i++) {
			int v = (s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10);
			q[4 * i + 0] = (v >> 3) & 1;
			q[4 * i + 1] = (v >> 2) & 1;
			q[4 * i + 2] = (v >> 1) & 1;
			q[4 * i + 3] = (v >> 0) & 1;
			// printf("%d: %d%d%d%d\n", v, q[4 * i], q[4 * i + 1], q[4 * i + 2], q[4 * i + 3]);
		}
		if(lastans) for(int i = 0; i < 256; i++) q[i] = !q[i];
		lastans = 0;
		for(int i = 1; i <= n; i++) {
			int cnt = 0;
			for(int j = 0; j < 256; j++)
				cnt += (a[i][j] != q[j]);
			if(cnt <= k) { lastans = 1; break; }
		}
		printf("%d\n", lastans);
	}
	return 0;
}