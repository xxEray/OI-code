#include <iostream>
#include <algorithm>
#include <string>
using std::string;
using std::cin;
using std::cout;

string s;
int n;

int main() {
	int T; cin >> T;
	while(T--) {
		cin >> s;
		while(s.find("std::make_tuple") != string::npos) {
			auto pos = s.find("std::make_tuple");
			s.erase(pos, 15);
			// std::cout << s << '\n';
		}
		std::cout << s << '\n';
	}
	return 0;
} /*
2
(-2,3,3,std::make_tuple(3,3))
std::make_tuple(std::make_tuple(1,1,4,5,1,4))
*/