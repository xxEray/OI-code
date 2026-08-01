#include <cstdio>

const int N = 100 + 5;
const int M = 20000 + 5;

struct Dish { char name[35]; int price, filling; } a[N];
int n, m;

int f[N][M];

int main() {
	scanf("%d%d", &n, &m);
	m *= 1000;
	for(int i = 1; i <= n; i++) {
		double x;
		scanf("%s%d%.3lf", a[i].name, &a[i].price, &x);
		a[i].filling = x * 1000;
	}
	for(int i = 1; i <= n; i++)
		for(int j = )
	return 0;
}