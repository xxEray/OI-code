#include <cstdio>
#include <cstring>

const int N = 1e5 + 5;

char a[N], b[N], c[N];

int main() {
	int T;
	std::scanf("%d", &T);
	while(T--) {
		int x;
		std::scanf("%s%d", a + 1, &x);
		int n = std::strlen(a + 1);
		for(int i = 1; i <= n; i++) b[i] = '1';
		for(int i = 1; i <= n; i++) 
			if(a[i] == '0') {
				if(i - x >= 1) b[i - x] = '0';
				if(i + x <= n) b[i + x] = '0';
			} 
		b[n + 1] = '\0';
		for(int i = 1; i <= n; i++)
			c[i] = '0' + ((i - x >= 1 && b[i - x] == '1') || (i + x <= n && b[i + x] == '1'));
		c[n + 1] = '\0';
		if(!std::strcmp(a + 1, c + 1)) std::puts(b + 1);
		else std::puts("-1");
	}
	return 0;
}