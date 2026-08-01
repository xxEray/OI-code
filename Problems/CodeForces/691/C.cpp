#include <iostream>
#include <algorithm>
#include <string>

std::string s;

int main() {
	std::cin >> s;
	int dot = s.find_first_of('.');
	if(dot == (int)std::string::npos) s.push_back('.'), dot = s.find_first_of('.');
	int st = 0;
	while(s[st] == '0') st++;
	s = s.substr(st);
	while(s.back() == '0') s.pop_back();
	dot = s.find_first_of('.');
	// std::cout << "format: " << s << std::endl;
	if((int)s.size() == 1 && s[0] == '.') std::cout << 0;
	else if(s[0] != '.') { // xx.xxxx
		int n = 0;
		while(dot > 1) std::swap(s[dot], s[dot - 1]), dot--, n++;
		while(s.back() == '0') s.pop_back();
		if(s.back() == '.') s.pop_back();
		std::cout << s;
		if(n) std::cout << 'E' << n;
	} else { // .xxxxxxxx
		int n = -1;
		s = s.substr(1);
		st = 0;
		while(!s.empty() && s[st] == '0') st++, n--;
		s = s.substr(st);
		if((int)s.size() == 1) std::cout << s;
		else std::cout << s[0] << '.' << s.substr(1);
		if(n) std::cout << 'E' << n;
	}
	return 0;
}