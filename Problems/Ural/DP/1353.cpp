#include <cstdio>
#include <algorithm>

const int N = 12;
const int S = 81 + 5;

int f[N][S];
int s;

int main() {
	scanf("%d", &s);
	for(int i = 0; i <= std::min(s, 9); i++) f[1][i] = 1;
	for(int i = 1; i <= 9; i++)
		for(int j = 0; j <= s; j++)
			for(int k = 0; k <= 9 && j + k <= s; k++)
				f[i + 1][j + k] += f[i][j];
	printf("%d\n", f[9][s] + (s == 1));
	return 0;
}