#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 5e4 + 5;

int a[N], q[N];

int n;

int query(int x, int y, int z) {
	printf("? %d %d %d\n", x, y, z), fflush(stdout);
	int r; scanf("%d", &r);
	return r;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(a, 0, sizeof(a));
		memset(q, 0, sizeof(q));
		scanf("%d", &n);
		for(int i = 1; i <= n; i += 3) q[i] = query(i, i + 1, i + 2); 
		int one[2] = {-1, -1};
		for(int i = 1; i <= n - 3; i += 3) if(q[i] != q[i + 3]) {
			q[i + 1] = query(i + 1, i + 2, i + 3), q[i + 2] = query(i + 2, i + 3, i + 4);
			if(q[i] != q[i + 1]) one[1] = q[i] ? i : i + 3, one[0] = q[i] ? i + 3 : i;
			if(q[i + 1] != q[i + 2]) one[1] = q[i + 1] ? i + 1 : i + 4, one[0] = q[i + 1] ? i + 4 : i + 1;
			if(q[i + 2] != q[i + 3]) one[1] = q[i + 2] ? i + 2 : i + 5, one[0] = q[i + 2] ? i + 5 : i + 2;
			break;
		}
		a[one[0]] = 0, a[one[1]] = 1;
		// printf(". one: [0]=%d, [1]=%d\n", one[0], one[1]), fflush(stdout);
		for(int i = 1; i <= n; i += 3)
			if(!(i <= one[1] && one[1] <= i + 2) && !(i <= one[0] && one[0] <= i + 2)) {
				int x = query(one[!q[i]], i, i + 1), y = query(one[!q[i]], i, i + 2);
				a[i] = -1, a[i + 1] = a[i + 2] = !q[i];
				if(x == q[i]) a[i] = a[i + 1] = q[i];
				if(y == q[i]) a[i] = a[i + 2] = q[i];
				if(a[i] == -1) a[i] = !q[i], a[i + 1] = a[i + 2] = q[i];
			} else {
				if(i != one[0] && i != one[1]) a[i] = query(one[0], one[1], i);
				if(i + 1 != one[0] && i + 1 != one[1]) a[i + 1] = query(one[0], one[1], i + 1);
				if(i + 2 != one[0] && i + 2 != one[1]) a[i + 2] = query(one[0], one[1], i + 2);
			}
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += !a[i];
		printf("! %d ", cnt);
		for(int i = 1; i <= n; i++) if(!a[i]) printf("%d ", i);
		puts(""), fflush(stdout);
	}
	return 0;
}