#include <cstdio>
#include <algorithm>

int query(int a, int b) { int x; printf("? %d %d\n", a, b); fflush(stdout); scanf("%d", &x); return x; }
void answer(int x) { printf("! %d\n", x); fflush(stdout); }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int ans = 0;
		for(int i = 0; i < 30; i++) {
			int v = query((1 << i) - ans, (1 << i) - ans + (1 << (i + 1)));
			if(v == (1 << (i + 1))) ans |= 1 << i;
		}
		answer(ans);
	}
	return 0;
}