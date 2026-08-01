#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int l, r, K;
		scanf("%d%d%d", &l, &r, &K);
		int c = ((r - r % 2) - (l + l % 2)) / 2 + 1;
		puts(((l == r && l > 1) || r - l + 1 - c <= K) ? "YES" : "NO");
	}
	return 0;
}