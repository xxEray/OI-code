#include <cstdio>
#include <cstring>

const int N = 1e5 + 5;

int n, x;
char s[N], ret[N];

int main() {
	int _c;
	std::scanf("%d", &_c);
	for(int __ = 1; __ <= _c; __++) {
		#define setif(ind, val, com) ((0 <= (ind) && (ind) <= n - 1) && (com) ? (ret[(ind)] = (val), 1) : 0)
		std::scanf("%s%d", s, &x);
		n = std::strlen(s);
		for(int i = 0; i < n; i++) ret[i] = '\0';
		for(int i = 0; i < n; i++)	
			if(s[i] == '0')
				setif(i - x, '0', true), setif(i + x, '0', true);
		bool flag = true;
		for(int i = 0; i < n; i++)
			if(s[i] == '1') {
				int l = setif(i - x, '1', ret[i - x] != '0');
				int r = setif(i + x, '1', ret[i + x] != '0');
				if(l == 0 && r == 0) {
					std::printf("-1\n");
					flag = false;
					break;
				}
			}
		if(!flag) continue;
		for(int i = 0; i < n; i++)
			if(ret[i] == '\0') ret[i] = '1';
		ret[n] = '\0';
		std::printf("%s\n", ret);
	}
	return 0;
}