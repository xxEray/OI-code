#include <cstdio>
#include <algorithm>
#include <set>

int n;
std::multiset<int> st;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); st.insert(x); }
	int ans = 0;
	while(st.size() > 1) {
		int mx = *st.rbegin(), mn = *st.begin();
		st.erase(st.find(mx));
		if(mx % mn) st.insert(mx % mn);
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}