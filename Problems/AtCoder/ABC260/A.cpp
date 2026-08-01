#include <cstdio>
#include <algorithm>

char s[5];

int main() {
	scanf("%s", s + 1);
	if(s[1] == s[2] && s[2] == s[3]) puts("-1");
	else if(s[1] != s[2] && s[1] != s[3]) putchar(s[1]);
	else if(s[2] != s[1] && s[2] != s[3]) putchar(s[2]);
	else if(s[3] != s[1] && s[3] != s[2]) putchar(s[3]);
	return 0;
}