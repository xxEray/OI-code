#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 2e5 + 5;

char a[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", a + 1);
		n = strlen(a + 1);
		for(int i = 1; i <= n; i++) a[i] -= '0';
		bool fl = false;
		for(int i = 1; i < n; i++) if(a[i] + a[i + 1] >= 10) fl = true;
		if(fl) {
			for(int i = n; i > 1; i--) if(a[i] + a[i - 1] >= 10) {
				for(int j = 1; j < i - 1; j++) putchar(a[j] + '0');
				printf("%d", a[i - 1] + a[i]);
				for(int j = i + 1; j <= n; j++) putchar(a[j] + '0');
				break;
			}
		} else {
			printf("%d", a[1] + a[2]);
			for(int j = 3; j <= n; j++) putchar(a[j] + '0');
		}
		puts("");
	}
	return 0;
}