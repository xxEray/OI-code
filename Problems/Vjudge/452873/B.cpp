#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 5;

char s[N];
int n;

int sum[N], mx[N];
int ret[N];

int f(int m) {
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(s[i] == '?') {
			if(mx[i] + 2 * (cnt + 1) <= m) ret[i] = 1, cnt++;
			else ret[i] = -1;
		} else if(s[i] == '0') ret[i] = -1;
		else ret[i] = 1;
	for(int i = 1; i <= n; i++) ret[i] += ret[i - 1];
	return *std::min_element(ret, ret + n + 1);
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		if(s[i] == '?' || s[i] == '0') sum[i] = sum[i - 1] - 1;
		else sum[i] = sum[i - 1] + 1;
	for(int i = 1; i <= n; i++) mx[i] = sum[i];
	for(int i = n - 1; i >= 0; i--) mx[i] = std::max(mx[i], mx[i + 1]);
	int Z = mx[0];
	printf("%d\n", std::min(Z - f(Z), Z + 1 - f(Z + 1)));
	return 0;
} /*

*/