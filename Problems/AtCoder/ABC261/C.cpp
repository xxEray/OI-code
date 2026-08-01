#include <iostream>
#include <algorithm>
#include <string>
#include <map>

const int N = 2e5 + 5;

int n;
std::map<std::string, int> mp;

int main() {
	std::cin >> n;
	for(int i = 1; i <= n; i++) {
		std::string s;
		std::cin >> s;
		mp[s]++;
		if(mp[s] == 1) std::cout << s << '\n';
		else std::cout << s << '(' << mp[s] - 1 << ')' << '\n';
	}
	return 0;
}