#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e5 + 5;

int a[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	LL cnt = 0, ans = 0;
	for(int i = 1; i <= n; i++)
		if(a[i] == i) cnt++;
		else if(a[i] < i) ans += (a[a[i]] == i);
	ans += cnt * (cnt - 1) / 2;
	printf("%lld\n", ans);
	return 0;
}