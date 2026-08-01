#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 2e5 + 5;

int a[N], b[N];
int n, C;

int ans[N];

int main() {
	scanf("%d%d", &n, &C);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	for(int j = 0; j < 30; j++) {
		int reset = 0, value = 0, flip = 0, lastv = C >> j & 1;
		for(int i = 1; i <= n; i++) {
			int op = a[i], v = b[i] >> j & 1;
			if((op == 1 && v == 1) || (op == 2 && v == 0) || (op == 3 && v == 0)) {
				if(!reset) ans[i] |= (lastv ^= flip) << j;
				else ans[i] |= (value ^ flip) << j;
			} else if(op == 1 && v == 0) {
				reset = i, value = 0, flip = 0;
			} else if(op == 2 && v == 1) {
				reset = i, value = 1, flip = 0;
				ans[i] |= 1 << j;
			} else if(op == 3 && v == 1) {
				flip ^= 1;
				if(!reset) ans[i] |= (lastv ^= flip) << j;
				else ans[i] |= (value ^ flip) << j;
			}
		}
	}
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}