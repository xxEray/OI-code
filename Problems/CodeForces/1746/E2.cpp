#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;

int n;
int bit;
int a[100];

template<typename Func>
bool ask(Func func) {
	std::vector<int> vct;
	for(int i = 1; i <= n; i++) if(func(i)) vct.push_back(i);
	printf("? %d ", (int)vct.size());
	for(int v : vct) printf("%d ", v);
	puts("");
	fflush(stdout);
	char s[10];
	scanf("%s", s);
	return s[0] == 'Y'; // YES
}
void answer(int x) {
	if(x < 1 || x > n) return;
	printf("! %d\n", x);
	fflush(stdout);
	char s[10];
	scanf("%s", s);
	if(s[1] == ')') exit(0); // :)
}
void guess(int real) {
	int v = 0;
	for(int i = 1; i < 3 * bit; i++) {
		if(i > 1) real ^= a[i] == a[i - 1];
		if(i % 3 && real) v |= a[i] << (i / 3);
	}
	printf("want to answer %d\n", v);
	answer(v);
}

int main() {
	scanf("%d", &n);
	bit = 0;
	for(int i = 1; i < n; i <<= 1) bit++;
	for(int i = 0; i < bit; i++) {
		if(i) a[3 * i] = ask([&](int x) { return (x >> (i - 1) & 1) && !(x >> i & 1); });
		a[3 * i + 1] = ask([&](int x) { return x >> i & 1; });
		a[3 * i + 2] = !ask([&](int x) { return !(x >> i & 1); });
	}
	guess(0), guess(1);
	return 0;
} /*
0 !0 (0&!1) 1 !1 (1&!2) ...
*/