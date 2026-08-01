#include <cstdio>

typedef long long LL;

int main() {
	LL n;
	std::scanf("%lld", &n);
	LL pow3 = 3; // 枚举的 3 的倍数
	int cnt = 1;
	while(pow3 < n - 1) {
		LL t = n - pow3; // 剩下的数
		int cnt2 = 0;
		// 如果 t 是 3 的正整数次幂则输出
		while(t > 1 && t % 5 == 0) t /= 5, cnt2++;
		if(t == 1) { std::printf("%d %d\n", cnt, cnt2); return 0; }
		pow3 *= 3, cnt++;
	}
	std::printf("-1"); // 无解
	return 0;
}