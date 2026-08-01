#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 2e5 + 5;

char s[N];
int n;

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	std::sort(s + 1, s + n + 1);
	printf("%s\n", s + 1);
	return 0;
}