#include <iostream>
#include <algorithm>
#include <set>
#include <string>

const int N = 1e5 + 5;

int n, m;

std::string s[N];
std::set<std::string> st;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) std::cin >> s[i];
	for(int i = 1; i <= m; i++) { std::string str; std::cin >> str; st.insert(str); }
	for(int i = 1; i <= n; i++) std::cout << (st.find(s[i]) != st.end() ? "Yes" : "No") << '\n';
	return 0;
}