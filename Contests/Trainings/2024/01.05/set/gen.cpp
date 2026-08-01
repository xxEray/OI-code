#include <bits/stdc++.h>

typedef long long LL;

int rand(int l, int r) { return rand() % (r - l + 1) + l; }
LL rand(LL l, LL r) { return ((LL)rand() << 45 | (LL)rand() << 30 | rand() << 15 | rand()) % (r - l + 1) + l; }

const int MAXV = 40;
const int N = 1e5;

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("set.in", "w", stdout);
	LL V = MAXV;
	int n = N;
	printf("%lld %d\n", V, n);
	V = (1LL << V) - 1;
	std::set<LL> st;
	for(int i = 1; i <= n; i++) {
		int t = rand(1, 2);
		if(t == 1) {
			LL v;
			do {
				v = rand(0LL, V);
			} while(st.count(v));
			st.emplace(v);
			printf("1 %lld\n", v);
		} else printf("2 %lld\n", rand(0LL, V));
	}
	return 0;
}
