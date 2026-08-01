#include <bits/stdc++.h>

const int N = 20000 + 5;
const char single[30][20] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char tens[20][20] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

char str[N];
int issingle(const char *str) {
	for(int i = 1; i <= 19; i++) if(!stricmp(str, single[i])) return i;
	return 0;
}
int istens(const char *str) {
	for(int i = 2; i <= 9; i++) if(!stricmp(str, tens[i])) return i * 10;
	return 0;
}

int main() {
	int num = 0, now = 0, level = 0;
	int flag = false, last = 0;
	while(scanf("%[a-zA-Z]", str)) {
		bool oldflag = flag;
		flag = true;
		if(!stricmp(str, "million") || !stricmp(str, "thousand")) {
			
		} else if(!stricmp(str, "hundred")) {

		} else if(issingle(str)) {

		} else if(istens(str)) {

		} else flag = false;
		if(!flag) {
			if(oldflag) printf("%d")
			while(last--) putchar('\n');
		}
		scanf("%*[,.!?:;() \r\n]", str);
		last = 0;
		for(int i = 0; str[i]; i++) if(str[i] == '\n') last++;
	}
	return 0;
}