#include <cstdio>
#include <cstring>

const int N = 2e5 + 5;

char s[N];
int cnt[10];

int main() {
	std::scanf("%s", s);
	int len = std::strlen(s);
	if(len < 3) {
		if(len == 3)
			for(int i = 0; i < len; i++)
				for(int j = 0; j < len; j++) {
					if(i != j)
						for(int k = 0; k < len; k++) 
							if(i != k && j != k) {
								int x = (s[i] - '0') * 100 + (s[j] - '0') * 10 + (s[k] - '0') * 1;
								if(x % 8 == 0) { std::puts("Yes"); return 0; }
							}
				}
		else if(len == 2) 
			for(int i = 0; i < len; i++)
				for(int j = 0; j < len; j++) {
					if(i != j) {
						int x = (s[i] - '0') * 10 + (s[j] - '0') * 1;
						if(x % 8 == 0) { std::puts("Yes"); return 0; }
					}
				}
		else if(len == 1 && s[0] == '8') { std::puts("Yes"); return 0; }
		std::puts("No");
		return 0;
	}
	for(int i = 0; i < len; i++) cnt[s[i] - '0']++;
	for(int i = 8; i < 1000; i += 8) {
		int t[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		t[i % 10]++, t[i / 10 % 10]++, t[i / 100]++;
		bool ok = true;
		for(int j = 0; j < 10; j++) ok &= (cnt[j] >= t[j]);
		if(ok) { std::puts("Yes"); return 0; }
	}
	std::puts("No");
	return 0;
}