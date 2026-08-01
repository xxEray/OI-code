#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>

const int N = 400 + 5;

int a[N], b[N], c[N];
int n;

int rand(int rbd) {
	int max = 32767 / rbd * rbd;
	int x;
	do x = rand(); while(x >= max);
	return x % rbd;
}

int main() {
	srand(time(0));
	scanf("%d", &n);
	int sum = 0;
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), a[i] += sum, sum = a[i];
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
	long long count = 0, times = 0;
	long long T = 1e15;
	while(T--) {
		int TT = std::min(T, 500000LL);
		while(TT--) {
			for(int i = 1; i <= n; i++) c[i] = 0;
			int cnt = 0, tot = 0;
			while(cnt < n) {
				int x = rand(sum) + 1, id;
				for(int j = 1; j <= n; j++) if(x > a[j - 1] && x <= a[j]) { id = j; break; }
				c[id]++;
				if(c[id] == b[id]) cnt++;
				tot++;
				// SetConsoleCursorPosition(handle, (COORD){0, 0});
				// printf("Get number %d, used %d numbers.\n", id, tot);
			}
			count += tot, times++;
			// SetConsoleCursorPosition(handle, (COORD){0, 1});
			// if(!(T & 0xfff)) printf("Summary: used %d numbers, expect = %.5lf\n", tot, (double)count / times);
		}
		SetConsoleCursorPosition(handle, (COORD){0, 0});
		printf("Summary: calculate %lld times, expect = %.10lf\n", times, (double)count / times);
	}
	return 0;
}