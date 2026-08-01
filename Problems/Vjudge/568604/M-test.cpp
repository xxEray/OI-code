#include <bits/stdc++.h>

struct A {
    int f() { static int cnt = 0; return ++cnt; }
} a, b;

int main() {
    std::cout << a.f() << std::endl;
    std::cout << b.f() << std::endl;
	return 0;
}