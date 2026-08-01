#include <cstdio>

const int N = 1e5 + 5;

char s[N];
int n;

int main() {
	scanf("%d%s", &n, s);
	for(int i = 0; i < n; i++) if(s[i] == '1') { puts(i & 1 ? "Aoki" : "Takahashi"); break; }
	return 0;
}