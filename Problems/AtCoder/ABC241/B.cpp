#include <cstdio>
#include <algorithm>
#include <set>

const int N = 1000 + 5;

std::multiset<int> st;
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); st.insert(x); }
	bool flag = true;
	for(int i = 1; i <= m; i++) { int x; scanf("%d", &x); if(st.find(x) == st.end()) flag = false; else st.erase(st.find(x)); }
	puts(flag ? "Yes" : "No");
	return 0;
}