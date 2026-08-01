#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
int n;

double f[N];
bool check_average(double average) {
	for(int i = 1; i <= n; i++)
		f[i] = std::max(f[i - 1] + a[i] - average, f[i - 2] + a[i] - average);
	return std::max(f[n - 1], f[n]) >= 0;
}
void get_average() {
	double l = *std::min_element(a + 1, a + n + 1) - 1, r = *std::max_element(a + 1, a + n + 1) + 1;
	int cnt = 0;
	while(l <= r && ++cnt <= 50) {
		double mid = (l + r) / 2;
		if(check_average(mid)) l = mid;
		else r = mid;
	}
	printf("%.5lf\n", l);
}

bool vis[N];
int tmp[N], cc;
bool check_median(LL median) {
	for(int i = 1; i <= n; i++) vis[i] = false;
	LL sum = 0, cnt = 0;
	for(int i = 1; i <= n; i++) if(a[i] >= median) sum += a[i], cnt++, vis[i] = true;
	int last = 0;
	for(int i = 1; i <= n; i++)
		if(vis[i]) last = i;
		else if(i - last >= 2) sum += a[i], cnt++, last = i, vis[i] = true;
	cc = 0;
	for(int i = 1; i <= n; i++) if(vis[i]) tmp[++cc] = a[i];
	std::sort(tmp + 1, tmp + cc + 1);
	return tmp[(cc + 1) >> 1] >= median;
}
void get_median() {
	LL l = *std::min_element(a + 1, a + n + 1), r = *std::max_element(a + 1, a + n + 1) + 1;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(check_median(mid)) l = mid + 1;
		else r = mid;
	}
	printf("%lld\n", l - 1);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	get_average();
	get_median();
	return 0;
} /*
6
2 1 2 1 1 10
*/