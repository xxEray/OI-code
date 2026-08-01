#include <bits/stdc++.h>

typedef unsigned long long ull;

int main() {
	ull x, y, w;
	scanf("%llu%llu%llu", &x, &y, &w);
	ull mn = x ^ y;
	printf("z = %llu: %llu ^ %llu = %llu\n", 0llu, x, y, mn);
	for(ull z = 1; z <= w; z++)
		if(((x + z) ^ (y + z)) < mn)
			mn = ((x + z) ^ (y + z)), printf("z = %llu: %llu ^ %llu = %llu\n", z, x + z, y + z, mn);
	return 0;
}