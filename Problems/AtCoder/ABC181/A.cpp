#include <cstdio>

int main() {
	int x;
	std::scanf("%d", &x);
	std::printf("%s", x & 1 ? "Black" : "White");
	return 0;
}