#include <cstdio>
#include <algorithm>
#include <cstring>

const int pow3[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683};

int n, m;

char s[11];
int cntR = 0;

int main() {
	scanf("%d%d%s", &n, &m, s);
	m = strlen(s);
	for(int i = 0; i < m; i++) cntR += (s[i] == 'R');
	
	return 0;
}