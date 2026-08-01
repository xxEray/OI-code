#include <cstdio>
#include <algorithm>
#include <string>

typedef long long LL;

const int N = 1e6 + 5;

std::string s;
int n;
LL x;

int main() {
	scanf("%d%lld", &n, &x);
	for(int i = 1; i <= n; i++) {
		char tmp[3];
		scanf("%1s", tmp);
		if(tmp[0] == 'U' && !s.empty() && s.back() != 'U') s.pop_back();
		else s.push_back(tmp[0]);
	}
	for(auto c : s)
		if(c == 'U') x >>= 1;
		else if(c == 'L') x <<= 1;
		else if(c == 'R') x = x << 1 | 1;
	printf("%lld\n", x);
	return 0;
}