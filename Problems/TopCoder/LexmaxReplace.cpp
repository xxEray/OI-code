#include <iostream>
#include <algorithm>
#include <string>
using std::string;

const int N = 50 + 5;

bool cmp(char a, char b) { return a > b; }

class LexmaxReplace {
public:
	string get(string s, string t) {
		sort(t.begin(), t.end(), cmp);
		int i = 0, j = 0;
		for(i = 0; i < (int)s.size() && j < (int)t.size(); i++)
			if(s[i] < t[j])
				s[i] = t[j], j++;
		return s;
	}
};

int main() {
	LexmaxReplace T;
	std::cout << T.get("xldyzmsrrwzwaofkcxwehgvtrsximxgdqrhjthkgfucrjdvwlr", "xfpidmmilhdfzypbguentqcojivertdhshstkcysydgcwuwhlk");
	return 0;
}