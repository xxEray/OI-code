#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using std::vector;
using std::string;

const int INF = 0x3f3f3f3f;

string s, str;
int n;

class CalcButton {
public:
	string getDigits(vector<string> seq) {
		for(string &t : seq) s += t;
		n = s.size();
		int ans = INF;
		std::string ansstr = "000";
		for(int i = 0; i <= n - 3; i++) {
			int cnt = 0;
			str = s.substr(i, 3);
			for(int j = 0; j < n;) {
				if(s.substr(j, 3) == str) j += 3, cnt++;
				else j++, cnt++;
			}
			if(ans > cnt) ans = cnt, ansstr = str;
			else if(ans == cnt) ansstr = std::min(ansstr, str);
		}
		return ansstr;
	}
};