#include <bits/stdc++.h>

#define msg(...) fprintf(stderr, __VA_ARGS__)

const int N = 5e5 + 5;

int n, K;
int a[N];

bool point[N];
int mn[N], mx[N];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	bool is_ascending = true;
	for(int i = 1; i < n; i++) is_ascending &= (a[i] < a[i + 1]);
	if(is_ascending) { puts("NIE"); return 0; }
	if(K >= 4) {
		for(int i = 1; i < n; i++) if(a[i] >= a[i + 1]) {
			puts("TAK");
			point[i - 1] = point[i] = point[i + 1] = true;
			int cnt = K - 2;
			if(i - 1 >= 1) cnt--;
			if(i + 1 < n) cnt--;
			for(int j = 1; j < n && cnt; j++) if(!point[j]) point[j] = true, cnt--;
			for(int j = 1; j < n; j++) if(point[j]) printf("%d ", j);
			puts("");
			break;
		}
	} else if(K == 1) puts("TAK");
	else if(K == 2) {
		mn[1] = a[1];
		for(int i = 2; i <= n; i++) mn[i] = std::min(mn[i - 1], a[i]);
		mx[n] = a[n];
		for(int i = n - 1; i >= 1; i--) mx[i] = std::max(mx[i + 1], a[i]);
		for(int i = 1; i < n; i++) if(mn[i] >= mx[i + 1]) {
			printf("TAK\n%d\n", i);
			return 0;
		}
		puts("NIE");
	} else {
		int mnpos = 1, mxpos = n;
		for(int i = 1; i <= n; i++) if(a[i] <= a[mnpos]) mnpos = i;
		for(int i = n; i >= 1; i--) if(a[i] >= a[mxpos]) mxpos = i;
		// msg("mnpos = %d, mxpos = %d\n", mnpos, mxpos);
		if(mnpos == 1 && mxpos == n) puts("NIE");
		else if(mnpos != 1) {
			if(mnpos != n) printf("TAK\n%d %d\n", mnpos - 1, mnpos);
			else printf("TAK\n1 %d\n", n - 1);
		} else {
			if(mxpos != 1) printf("TAK\n%d %d\n", mxpos - 1, mxpos);
			else printf("TAK\n1 %d\n", n - 1);
		}
	}
	return 0;
}