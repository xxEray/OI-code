#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 100 + 5;

int n, k;

int t1[N], t2[N], t3[N], zero[N];

void change(int x, int *const y) {
	memset(y, 0, sizeof(int) * N);
	for(int i = 1; x; i++) y[i] = x % k, x /= k, y[0] = i;
	while(y[y[0]] == 0) y[0]--;
}

void cxor(const int *const x, const int *const y, int *const z) { // x ^ y = z
	memset(z, 0, sizeof(int) * N);
	z[0] = std::max(x[0], y[0]);
	for(int i = 1; i <= std::max(x[0], y[0]); i++)
		z[i] = (x[i] + y[i]) % k;
	while(z[z[0]] == 0) z[0]--;
}

void caxor(const int *const x, const int *const y, int *const z) { // y ^ z = x (aka x - y = z)
	memset(z, 0, sizeof(int) * N);
	z[0] = std::max(x[0], y[0]);
	for(int i = 1; i <= std::max(x[0], y[0]); i++)
		z[i] = (x[i] - y[i] + k) % k;
	while(z[z[0]] == 0) z[0]--;
}

void change(const int *const x, int &y) {
	y = 0;
	for(int i = x[0]; i >= 1; i--) y = y * k + x[i];
}

void print(int *const x) {
	printf("(");
	for(int i = 1; i <= x[0]; i++) printf("%d,", x[i]);
	printf("\b) ");
}

void copy(int *const x, const int *const y) {
	for(int i = 0; i < N; i++) x[i] = y[i];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(t1, 0, sizeof(t1));
		scanf("%d%d", &n, &k);
		for(int i = 0; i < n; i++) {
			int x;
			change(i, t2);
			if(i & 1) caxor(t1, t2, t3);
			else cxor(t1, t2, t3);
			change(t3, x);
			printf("%d\n", x);
			fflush(stdout);
			int status;
			scanf("%d", &status);
			if(status == 0) caxor(zero, t1, t2), cxor(t3, t2, t1);
			else break;
		}
	}
	return 0;
} /*
x --- y1
y1 - x --- y1 - y2
y2 - (y1 - x) --- y2 - (y1 - y3) = y2 - y1 + y3
y3 - (y2 - (y1 - x)) --- y3 - (y2 - (y1 - y4)) = y3 - y2 + y1 - y4
*/