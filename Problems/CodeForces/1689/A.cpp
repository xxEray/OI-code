#include <cstdio>
#include <algorithm>

const int N = 100 + 5;

int n, m, K;

struct Character { int t; char c; } a[N * 2];
bool operator<(Character x, Character y) { return x.c < y.c; }
char tmp[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &K);
		scanf("%s", tmp);
	}
	return 0;
}