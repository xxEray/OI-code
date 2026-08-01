#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

const int N = 2000 + 5;

int a[N], b[N];
int n;

std::multiset<int> st;
std::vector<int> ans;

bool check(int x) {
	st.clear();
	for(int i = 1; i <= n; i++) st.insert(b[i]);
	for(int i = 1; i <= n; i++)
		if(st.find(a[i] ^ x) == st.end()) return false;
		else st.erase(st.find(a[i] ^ x));
	return true;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) if(check(a[1] ^ b[i])) ans.push_back(a[1] ^ b[i]);
	std::sort(ans.begin(), ans.end());
	ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
	printf("%d\n", (int)ans.size());
	for(int x : ans) printf("%d\n", x);
	return 0;
}