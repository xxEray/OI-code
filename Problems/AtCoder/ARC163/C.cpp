#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;

int n;
std::set<LL> st;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		if(n == 1) { printf("Yes\n1\n"); continue; }
		else if(n == 2) { puts("No"); continue; }
		st.clear();
		st.insert(2), st.insert(3), st.insert(6);
		while((int)st.size() < n) {
			for(LL x : st) if(!st.count(x + 1) && !st.count(x * (x + 1)) && x * (x + 1) <= 1000000000)
				{ st.erase(x), st.insert(x + 1), st.insert(x * (x + 1)); break; }
		}
		puts("Yes");
		for(LL x : st) printf("%lld ", x);
		puts("");
	}
	return 0;
}