#include <bits/stdc++.h>

int n;
std::map<std::string, int> mp;

int main() {
	std::cin >> n;
	for(int i = 1; i <= n; i++) { std::string s; std::cin >> s; mp[s]++; }
	int mx = 0;
	for(auto [s, c] : mp) mx = std::max(mx, c);
	for(auto [s, c] : mp) if(c == mx) std::cout << s << '\n';
	return 0;
}