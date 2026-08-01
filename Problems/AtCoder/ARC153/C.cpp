#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 2e5 + 5;

int n;
int a[N];

LL ans[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL sum = 0;
	for(int i = 1; i <= n; i++) sum += a[i] * i, ans[i] = i;
	LL x = 0;
	for(int i = 1; i <= n; i++) {
		x += a[i];
		if(sum < 0 && x < 0) {
			if(a[n] == -1) {
				LL v = (-sum - 1) / -x + 1; // ceil(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = 1; j <= i; j++) ans[j] += -v, sum += a[j] * -v;
				assert(sum >= 0);
				ans[n] += sum, sum = 0;
				break;
			} else { // a[n] == 1
				LL v = -sum / -x; // floor(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = 1; j <= i; j++) ans[j] += -v, sum += a[j] * -v;
				assert(sum <= 0);
				ans[n] += -sum, sum = 0;
				break;
			}
		} else if(sum > 0 && x > 0) {
			if(a[n] == -1) {
				LL v = (sum - 1) / x + 1; // ceil(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = 1; j <= i; j++) ans[j] += -v, sum += a[j] * -v;
				assert(sum >= 0);
				ans[n] += sum, sum = 0;
				break;
			} else { // a[n] == 1
				LL v = sum / x; // floor(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = 1; j <= i; j++) ans[j] += -v, sum += a[j] * -v;
				assert(sum <= 0);
				a[n] += -sum, sum = 0;
				break;
			}
		}
	}
	if(sum == 0) {
		puts("Yes");
		for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
		return 0;
	}
	x = 0;
	for(int i = n; i >= 1; i--) {
		x += a[i];
		if(sum < 0 && x > 0) {
			if(a[n] == -1) {
				LL v = (-sum - 1) / x + 1; // ceil(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = n; j >= i; j--) ans[j] += v, sum += a[j] * v;
				assert(sum >= 0);
				ans[n] += sum, sum = 0;
				break;
			} else { // a[n] == 1
				LL v = -sum / x; // floor(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = n; j >= i; j--) ans[j] += v, sum += a[j] * v;
				assert(sum <= 0);
				a[n] += -sum, sum = 0;
				break;
			}
		} else if(sum > 0 && x < 0) {
			if(a[n] == -1) {
				LL v = sum / -x; // floor(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = n; j >= i; j--) ans[j] += v, sum += a[j] * v;
				assert(sum >= 0);
				a[n] += sum, sum = 0;
				break;
			} else { // a[n] == 1
				LL v = (sum - 1) / -x + 1; // ceil(abs(sum) / abs(x))
				assert(v >= 0);
				for(int j = n; j >= i; j--) ans[j] += v, sum += a[j] * v;
				assert(sum <= 0);
				a[n] += -sum, sum = 0;
				break;
			}
		}
	}
	if(sum == 0) {
		puts("Yes");
		for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
		return 0;
	}
	puts("No");
	return 0;
}