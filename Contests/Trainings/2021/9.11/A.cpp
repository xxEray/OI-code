#include <cstdio>
#include <algorithm>

typedef long long LL;

int n;

namespace BaoLi {
	int a[100], b[100];
	void bin(LL x, int *arr) { for(int i = 63; i >= 0; i--) arr[i] = (x >> i & 1); }
	void to_dec(LL &x, int *arr) { x = 0; for(int i = 63; i >= 0; i--) x = x * 10 + arr[i]; }
	bool suffix(int *x, int *y) {
		int len = 63;
		while(!a[len]) len--;
		for(int i = len; i >= 0; i--) if(x[i] != y[i]) return false;
		return true;
	}
	void main() {
		int cnt = 0;
		for(int i = 1; i <= 100000; i++) {
			LL x;
			bin(i, a), to_dec(x, a), bin(x, b);
			if(suffix(a, b)) {
				cnt++;
				if(cnt == n) {
					int j = 63;
					while(j && !a[j]) j--;
					while(j >= 0) printf("%d", a[j]), j--;
					break;
				}
			} 
		}
	}
	
}

namespace DaBiao {
	int a[100], b[100];
	void bin(LL x, int *arr) { for(int i = 63; i >= 0; i--) arr[i] = (x >> i & 1); }
	void to_dec(LL &x, int *arr) { x = 0; for(int i = 63; i >= 0; i--) x = x * 10 + arr[i]; }
	bool suffix(int *x, int *y) {
		int len = 63;
		while(!a[len]) len--;
		for(int i = len; i >= 0; i--) if(x[i] != y[i]) return false;
		return true;
	}
	void main() {
		for(int i = 1; i <= n; i++) {
			LL x;
			bin(i, a), to_dec(x, a), bin(x, b);
			int j = 63;
			while(j && !a[j]) j--;
			while(j >= 0) printf("%d", a[j]), j--;
			if(suffix(a, b)) puts(" is OK!");
			else puts(" is Wrong!");
		}
	}
}

namespace LuanGao {
	int a[100], b[100], c[100], ok[100];
	void clear(int *arr) { for(int i = 0; i< 100; i++) arr[i] = 0;}
	LL dec_of(int *arr) { LL x = 0; for(int i = 63; i >= 0; i--) x = x * 10 + arr[i]; return x; }
	LL bin_of(int *arr) { LL x = 0; for(int i = 63; i >= 0; i--) x = x << 1 | arr[i]; return x; }
	void dec_to(LL x, int *arr) { for(int i = 0; i <= 63; i++) arr[i] = x % 10, x /= 10; }
	void bin_to(LL x, int *arr) { for(int i = 63; i >= 0; i--) arr[i] = (x >> i & 1); }
	void main() {
		LL rest = n;
		for(int i = 1; i <= 63; i++) {
			LL lastbit = i - 1, w = (1 << i), okcnt = 0;
			ok[i - 1] = true;
			for(int j = 0; j < 100; j++) ok[j] = false;
			for(int j = i - 2; j >= 0; j--) {
				clear(a), a[j] = 1;
				clear(b), b[lastbit] = 1;
				LL now = dec_of(a), last = dec_of(b);
				LL retd = (last - now) % w;
				now = bin_of(a), last = bin_of(b);
				LL retb = (last - now) % w;
				if(retd == retb) ok[j] = true, okcnt++, lastbit = j;
			}
			if(rest > (1LL << okcnt)) rest -= (1LL << okcnt);
			else {
				clear(c);
				rest--;
				c[i - 1] = 1;
				for(int j = okcnt - 1, k = 63; j >= 0; j--) {
					while(!ok[k]) k--;
					c[k] = (rest >> j & 1);
					k--;
				}
				bool flag = false;
				for(int j = 63; j >= 0; j--) flag |= c[j], (flag ? printf("%d", c[j]) : 0);
				puts("");
				break;
			}
		}
	}
}

int main() {
// #ifndef DEBUG
// 	freopen("binary.in", "r", stdin);
// 	freopen("binary.out", "w", stdout);
// #endif
	scanf("%d", &n);
	// LuanGao::main(); return 0;
	// DaBiao::main(); return 0;
	if(n <= 100) BaoLi::main();
	else LuanGao::main();
	return 0;
}
