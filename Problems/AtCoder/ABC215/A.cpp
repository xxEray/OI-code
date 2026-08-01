#include <cstdio>
#include <cstring>

char s[20];

int main() {
	scanf("%s", s);
	if(!strcmp(s, "Hello,World!")) puts("AC");
	else puts("WA");
	return 0;
}