#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n, K;
int a[N], b[N];

int sl[N], sr[N];
bool check(LL pivot) {
	LL now = 0;
	std::priority_queue<int> st;
	for(int i = 1; i <= n; i++) {
		st.push(a[i]), now += a[i];
		while(now > pivot) now -= st.top(), st.pop();
		sl[i] = st.size();
	}
	now = 0;
	while(!st.empty()) st.pop();
	for(int i = n; i >= 1; i--) {
		st.push(a[i]), now += a[i];
		while(now > pivot) now -= st.top(), st.pop();
		sr[i] = st.size();
	}
	// for(int i = 1; i <= n; i++) printf("%d: sl = %d, sr = %d\n", i, sl[i], sr[i]);
	sr[n + 1] = 0;
	int ret = 0;
	for(int i = 1; i <= n; i++) ret = std::max(ret, sl[i] + sr[i + 1]);
	return ret >= K;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		LL sum = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
		std::sort(b + 1, b + n + 1);
		for(int i = 1; i <= K; i++) sum += b[i];
		LL l = sum / 2, r = sum;
		while(l < r) {
			LL mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%lld\n", l);
	}
	return 0;
} /*
6
5 4
1 10 1 1 1
5 3
1 20 5 15 3
5 3
1 20 3 15 5
10 6
10 8 20 14 3 8 6 4 16 11
10 5
9 9 2 13 15 19 4 9 13 12
1 1
1
*/