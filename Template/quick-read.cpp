template<class T> inline void read(T &x) {
	char ch = getchar();
	x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while('0' <= ch && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
}
template<class T> inline void wrt(T x, char c = 0) {
	int t[60] = {0}, pos = 0;
	while(x) t[++pos] = x % 10, x /= 10;
	if(!pos) putchar('0');
	else while(pos) putchar(t[pos--] + '0');
	if(c) putchar(c);
}