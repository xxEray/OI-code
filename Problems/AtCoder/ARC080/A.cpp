#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;
int a[N];

int main() {
	scanf("%d", &n);
	int cnt1 = 0, cnt2 = 0, cnt4 = 0;
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		if(x % 4 == 0) cnt4++;
		else if(x % 2 == 0) cnt2++;
		else cnt1++;
	}
	puts((cnt1 > cnt4 && cnt2) || (cnt1 > cnt4 + 1) ? "No" : "Yes");
	return 0;
}