#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1000 + 5;

//                abcdefghijklmnopqrstuvwxyz
const char p[] = " d b          oqp    vwx  ";
//                ABCDEFGHIJKLMNOPQRSTUVWXYZ
const char P[] = "A      HI   M O    TUVWXY ";

char s[N];
int n;

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1, j = n; i <= j; i++, j--)
		if(s[i] >= 'a' ? p[s[i] - 'a'] != s[j] : P[s[i] - 'A'] != s[j])
			{ puts("NIE"); return 0; }
	puts("TAK");
	return 0;
}