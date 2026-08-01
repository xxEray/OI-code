#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>

std::string s;
int n;

int main() {
	int T; std::cin >> T;
	while(T--) {
		std::cin >> s;
		s.front() = s.back();
		std::cout << s << std::endl;
	}
	return 0;
}