#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 1000 + 5;

char a[N];
int n;

char s[N], alter[N];

int query(const char *str) {
	printf("%s\n", str + 1);
	fflush(stdout);
	int x;
	scanf("%d", &x);
	if(x == -1 || x == n) exit(0);
	return x;
}
char flip(char c) { return c == 'T' ? 'F' : 'T'; }

int main() {
	scanf("%d", &n);
	alter[n + 1] = s[n + 1] = '\0';
	for(int i = 1; i <= n; i++) s[i] = 'T';
	int allT = query(s);
	for(int i = 1; i <= n; i++) alter[i] = (i & 1) ? 'T' : 'F';
	int alternative = query(alter);
	int ptr = n / 3 * 2 + 1;
	for(int i = 1; i <= n / 3 * 2; i += 2) {
		s[i] = s[i + 1] = 'F';
		int x = query(s);
		s[i] = s[i + 1] = 'T';
		if(allT - x) {
			if(allT - x == 2) a[i] = a[i + 1] = 'T';
			else if(allT - x == -2) a[i] = a[i + 1] = 'F';
			else assert(false);
		} else {
			alter[i] = 'F', alter[i + 1] = 'T', alter[ptr] = flip(alter[ptr]);
			int y = query(alter);
			alter[i] = 'T', alter[i + 1] = 'F', alter[ptr] = flip(alter[ptr]);
			if(alternative - y == 3) a[i] = 'T', a[i + 1] = 'F', a[ptr] = alter[ptr];
			else if(alternative - y == 1) a[i] = 'T', a[i + 1] = 'F', a[ptr] = flip(alter[ptr]);
			else if(alternative - y == -1) a[i] = 'F', a[i + 1] = 'T', a[ptr] = alter[ptr];
			else if(alternative - y == -3) a[i] = 'F', a[i + 1] = 'T', a[ptr] = flip(alter[ptr]);
			else assert(false);
			ptr++;
		}
	}
	while(ptr <= n) {
		s[ptr] = 'F';
		int x = query(s);
		a[ptr] = (allT - x == 1 ? 'T' : 'F');
		s[ptr] = 'T';
		ptr++;
	}
	query(a); // should be n
	return 0;
} /*
*/