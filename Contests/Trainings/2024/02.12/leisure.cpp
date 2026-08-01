#include <bits/stdc++.h>

const int N = 2e6 + 5;

int n, Q;
int a[N];

int main() {
#ifndef DEBUG
	freopen("leisure.in", "r", stdin);
	freopen("leisure.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
	while(Q--) {
		int t, l, r;
		scanf("%d%d%d", &t, &l, &r);
		if(t == 1) {
			for(int i = l; i < r; i++)
				if(a[i] == 0 && a[i + 1] == 1)
					std::swap(a[i], a[i + 1]), i++;
		} else if(t == 2) {
			for(int i = l; i < r; i++)
				if(a[i] == 1 && a[i + 1] == 0)
					std::swap(a[i], a[i + 1]), i++;
		} else {
			int sum = 0;
			for(int i = l; i <= r; i++) sum += a[i];
			printf("%d\n", sum);
		}
	}
	return 0;
}