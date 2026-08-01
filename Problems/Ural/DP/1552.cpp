#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 50 + 3;
const int LETTER = 26 + 3;
const int SEAT = 4 + 1;

char s[LEN];
int n;

int f[LEN][SEAT][LETTER][LETTER][LETTER];
int last[LEN][SEAT][LETTER][LETTER][LETTER];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < 4; j++)
			for(int k0 = 0; k0 <= 26; k0++)
				for(int k1 = 0; k1 <= 26; k1++)
					for(int k2 = 0; k2 <= 26; k2++) {
						f[i][j][k0][k1][k2]
					}
	return 0;
}