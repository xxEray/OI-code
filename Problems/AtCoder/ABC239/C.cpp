#include <cstdio>
#include <algorithm>

const int xs[] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
const int ys[] = {0, 2, 1, -1, -2, -2, -1, 1, 2};

int main() {
	long long x1, y1, x2, y2;
	scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
	int cnt = 0;
	for(int i = 1; i <= 8; i++) {
		long long tx = x2 + xs[i], ty = y2 + ys[i];
		cnt += ((long long)(x1 - tx) * (x1 - tx) + (long long)(y1 - ty) * (y1 - ty) == 5);
	}
	puts(cnt >= 1 ? "Yes" : "No");
	return 0;
}