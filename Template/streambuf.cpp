#include <iostream>
#include <streambuf>
inline char rdc() {
	const int D = 1 << 23;
	static char buf[D], *p1, *p2;
	static std::streambuf *in = std::cin.rdbuf();
	return (p1 == p2 && (p2 = (p1 = buf) + in->sgetn(buf, D), p1 == p2) ? -1 : *p1++);
}
template<typename T> void read(T &x) {
	char c = rdc(), fl = 0;
	while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
	for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
    if(fl) x = -x;
}
inline void wrtc(char c) {
	static std::streambuf *out = std::cout.rdbuf();
	out->sputc(c);
}
template<typename T> void write(T x, char ch = 0) {
	static char c[60]; int top = 0;
    if(x < 0) wrtc('-'), x = -x;
	do c[++top] = x % 10, x /= 10; while(x);
	while(top) wrtc(c[top--] + '0');
	if(ch) wrtc(ch);
}