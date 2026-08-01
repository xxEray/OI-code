#include <cstdio>
#include <algorithm>
const int N = 5e5 + 5;
typedef long long LL;
// qio内容为 fread, fwrite 快速输入输出模板 
namespace qio { // quick-inupt-output
	const int D = (1 << 10) + 1;
	char in[D], *I = in, *Iend = in;
	char qgetc() { // quick-get-charter，如果在控制台调试，需要输入Ctrl+Z
		if(I == Iend) {
			Iend = in + fread(I = in, 1, D, stdin);
			if(feof(stdin)) return EOF; // read an EOF (End-Of-File)
			return *I++; // *I++ ==> *(I++) ==> *I, I++
		} else return *I++;
	}
	template<typename Tp> void getnum(Tp &x) { // get-number
		char ch; bool f = false;
		for(ch = qgetc(); ch < '0' || ch > '9'; ch = qgetc()) f |= (ch == '-');
		for(x = 0; '0' <= ch && ch <= '9'; ch = qgetc()) x = x * 10 + (ch ^ 48);
		if(f) x = -x;
	}
	// get-multi-number (C++11)
	template<typename Tp, typename ...Tps> void getnum(Tp &x, Tps &...xs) { getnum(x); getnum(xs...); }
	// output
	char out[D], *O = out;
	void qputc(char ch) { // quick-put-charter，需要调用flush()！ 
		if(O == out + D) fwrite(O = out, 1, D, stdout);
		*O++ = ch; // *O++ = ch ==> *O = ch, O++
	}
	template<typename Tp> void putnum(Tp x) { // put-number
		char s[20]; int top = 0;
		if(x < 0) qputc('-'), x = -x;
		if(x == 0) s[top++] = '0';
		for(; x; x /= 10) s[top++] = x % 10 + '0';
		for(top--; top >= 0; top--) qputc(s[top]);
	}
	// put-numti-number (C++11)
	template<typename Tp, typename ...Tps> void putnum(Tp x, Tps ...xs) { putnum(x); putnum(xs...); }
	inline void flush() { fwrite(out, 1, O - out, stdout); }
}
// qio模板结束 
struct Ask {
	int l, r, id;
	bool operator<(const Ask &rhs) const { return r == rhs.r ? l < rhs.l : r < rhs.r; }
} q[N];
int a[N], lst[N];
LL ans[N];
int n, m;
namespace BIT { // 线段树模板 
	int c[N];
	inline int lowbit(int x) { return x & -x; }
	void add(int ind, int val) {
		for(; ind <= n; ind += lowbit(ind)) c[ind] += val;
	}
	int query(int x) {
		int total = 0;
		for(; x; x -= lowbit(x)) total += c[x];
		return total;
	}
}
int main() {
//	qio::getnum(n);
	scanf("%d", &n);
	scanf("%d", &m);
	for(int i = 1; i <= n; i++) //qio::getnum(a[i]);
		scanf("%d", &a[i]);
//	qio::getnum(m);
	for(int i = 1; i <= m; i++) //qio::getnum(q[i].l, q[i].r), q[i].id = i;
		scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	int j = 1;
	for(int i = 1; i <= m; i++) {
		for(; j <= q[i].r; j++) {
			if(lst[a[j]])
				BIT::add(lst[a[j]], -1);
			BIT::add(j, 1);
			lst[a[j]] = j;
		}
		j = q[i].r + 1;
		ans[q[i].id] = BIT::query(q[i].r) - BIT::query(q[i].l - 1);
	}
	for(int i = 1; i <= m; i++)
		printf("%lld\n", ans[i]);
//		qio::putnum(ans[i]), qio::qputc('\n'); // 注意输出换行！ 
//	qio::flush(); // 这一句一定不能掉！（或者把qio封装到class里，构析函数里加上这一句） 
	return 0;
} /*
// P1972 [SDOI2009]HH的项链
*/