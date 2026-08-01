#include <iostream>
#include <algorithm>
#include <string>

int n;
std::string s;

int main() {
	int T; std::cin >> T;
	while(T--) {
		std::cin >> n >> s;
		if(s.find("aa") != std::string::npos) std::cout << 2 << '\n';
		else if(s.find("aba") != std::string::npos) std::cout << 3 << '\n';
		else if(s.find("aca") != std::string::npos) std::cout << 3 << '\n';
		else if(s.find("abca") != std::string::npos) std::cout << 4 << '\n';
		else if(s.find("acba") != std::string::npos) std::cout << 4 << '\n';
		else if(s.find("abbacca") != std::string::npos) std::cout << 7 << '\n';
		else if(s.find("accabba") != std::string::npos) std::cout << 7 << '\n';
		else std::cout << -1 << '\n';
	}
	return 0;
} /*
abcbaca
*/