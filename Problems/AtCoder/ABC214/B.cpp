#include <cstdio>
#include <algorithm>

int s, t;

int main() {
	scanf("%d%d", &s, &t);
	int ans = 0;
	for(int i = 0; i <= s; i++)
		for(int j = 0; j <= s; j++)
			for(int k = 0; k <= s; k++)
				ans += (i + j + k <= s && i * j * k <= t);
	printf("%d\n", ans);
	return 0;
}