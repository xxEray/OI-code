#include <bits/stdc++.h>

const int N = 200 + 5;

int n;
char s[N];

int main() {
	scanf("%d%s", &n, s + 1);
	int suml = 0, sumo = 0;
	for(int i = 1; i <= n; i++) suml += (s[i] == 'L'), sumo += (s[i] == 'O');
	int nowl = 0, nowo = 0;
	for(int i = 1; i < n; i++) {
		if(s[i] == 'L') nowl++;
		else nowo++;
		if(nowl != suml - nowl && nowo != sumo - nowo) { printf("%d\n", i); return 0; }
	}
	puts("-1");
	return 0;
}