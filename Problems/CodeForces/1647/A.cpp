#include <cstdio>
#include <algorithm>
#include <string>

const int N = 1000 + 5;

std::string f[N][10];
int m;

const std::string &max_num(const std::string &s1, const std::string &s2) {
	if(s1.size() != s2.size()) return s1.size() > s2.size() ? s1 : s2;
	else return s1 > s2 ? s1 : s2;
}

int main() {
	for(int i = 1; i <= 1000; i++)
		for(int j = 1; j <= 9; j++) if(i >= j)
			for(int k = 1; k <= 9; k++) if(j != k)
				f[i][j] = max_num(f[i][j], f[i - j][k] + (char)(j + '0'));
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &m);
		std::string s = "";
		for(int j = 1; j <= 9; j++) s = max_num(s, f[m][j]);
		printf("%s\n", s.c_str());
	}
	return 0;
}