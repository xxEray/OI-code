#include "biginteger" // 高精模板库（我自己写的）

BigInteger k, l, n;

int main() {
	std::cin >> n >> k >> l;
	BigInteger g = gcd(k, l);
	if(n >= k + l - g) std::cout << g;
	else std::cout << k + l - n;
	return 0;
}