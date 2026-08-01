#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

const int N = 100 + 5;

char s[N], t[N], r[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		int len = strlen(s);
		bool flag = false;
		for(int i = 0, j = 0; i <= len; i++) {
			if(i == len || s[i] == '+') {
				int C;
				t[j] = '\0', sscanf(t, "%d%s", &C, r);
				if(!strcmp(r, "x")) { // Cx
					if(C > 0) flag = true;
				} else if(!strcmp(r, "^x")) { // C^x
					if(C > 1) flag = true;
				} else if(!strcmp(r, "/sinx")) { // C/sinx
					if(C) flag = true;
				} else if(!strcmp(r, "/cosx")) { // C/cosx
					if(C) flag = true;
				} else if(!strcmp(r, "sinx")) { // Csinx
					if(C) flag = true;
				} else if(!strcmp(r, "cosx")) { // Ccosx
					if(C) flag = true;
				} else if(!strcmp(r, "/x")) { // C/x
					if(C) flag = true;
				}
				if(flag) break;
				j = 0;
			} else t[j++] = s[i];
		}
		puts(flag ? "NO" : "YES");
	}
	return 0;
}