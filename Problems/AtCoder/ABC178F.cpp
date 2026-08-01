#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N], b[N];
int n;

bool check() {
	for(int i = 1; i <= n; i++) if(a[i] == b[i]) return false;
	return true;
}

int main() {
	std::scanf("%d", &n);
	for(int i = 1; i <= n; i++) std::scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) std::scanf("%d", &b[i]);
	std::reverse(b + 1, b + n + 1);
	int st = 0, num = -1;
	for(int i = 1; i <= n; i++)
		if(a[i] == b[i]) {
			st = i, num = a[i];
			break;
		}
	if(st)
		for(int i = 1; i <= n; i++)
			if(a[i] != num && b[i] != num) {
				std::swap(b[i], b[st++]);
				if(b[st] != num || a[st] != num) break;
			}
	if(check()) {
		std::printf("Yes\n");
		for(int i = 1; i <= n; i++) std::printf("%d ", b[i]);
	} else std::printf("No\n");
	return 0;
}