#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 2e6 + 5;

bool fl[N];
int p[N], c;
int t1[N], t2[N];

int main() {
	LL a, b, cnt = 0;
	scanf("%lld%lld", &a, &b);
	int mab = std::max(a, b);
	for(int i = 1; i <= mab; i++) fl[i] = true;
	for(int i = 2; i * i <= mab; i++)
		for(int j = i * i; j <= mab; j += i * i) fl[j] = false;
	for(int i = 1; i <= mab; i++) if(fl[i]) p[++c] = i;
	for(LL i = 1; i * i <= a; i++) t1[i] = std::upper_bound(p + 1, p + c + 1, a / (i * i)) - p - 1;
	for(LL i = 1; i * i <= b; i++) t2[i] = std::upper_bound(p + 1, p + c + 1, b / (i * i)) - p - 1;
	for(LL i = 1; i * i <= a; i++)
		for(LL j = 1; j * j <= b; j++) {
			cnt += std::min(t1[i], t2[j]);
//			printf("i^2 = %lld, j^2 = %lld, x = %lld, y = %lld\n", i * i, j * j, x, y);
		}
	printf("%lld\n", cnt);
	return 0;
} /*
5 5
*/
