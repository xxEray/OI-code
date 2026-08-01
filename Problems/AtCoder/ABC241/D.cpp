#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;

std::multiset<LL> st;
int Q;

int main() {
	scanf("%d", &Q);
	while(Q--) {
		int type; LL x; int k;
		scanf("%d%lld", &type, &x);
		if(type == 1) {
			st.insert(x);
		} else if(type == 2) {
			scanf("%d", &k);
			auto it = st.upper_bound(x);
			bool flag = true;
			for(int o = 1; o <= k; o++) {
				if(it == st.begin()) { flag = false; break; }
				it--;
			}
			if(flag) printf("%lld\n", *it);
			else puts("-1");
		} else {
			scanf("%d", &k);
			auto it = st.lower_bound(x);
			bool flag = true;
			if(it == st.end()) flag = false;
			else
				for(int o = 1; o < k; o++) {
					it++;
					if(it == st.end()) { flag = false; break; }
				}
			if(flag) printf("%lld\n", *it);
			else puts("-1");
		}
	}
	return 0;
}