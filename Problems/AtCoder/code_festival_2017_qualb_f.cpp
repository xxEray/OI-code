#include <bits/stdc++.h>
int a, b, c;
std::multiset<std::string> st;
int main() {
	scanf("%d%d%d", &a, &b, &c);
	while(a--) st.insert("a");
	while(b--) st.insert("b");
	while(c--) st.insert("c");
	while(st.size() > 1) {
		auto s = *st.begin(), t = *st.rbegin();
		st.erase(st.begin()), st.erase(--st.end());
		st.insert(s + t);
	}
	printf("%s\n", st.begin()->c_str());
	return 0;
}