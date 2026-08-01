#include <cstdio>

const int N = 50 + 5;

int a[N][N];

bool row[N][N], col[N][N];

int main() {
	int n, k;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			std::scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(i != j) {}
	return 0;
}