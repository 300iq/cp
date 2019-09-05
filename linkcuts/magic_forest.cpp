#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <queue>
#define For(i, a, b) for(register int i = a, ___u = b; i <= ___u; ++i)
#define ForDown(i, a, b) for(register int i = b, ___d = a; i >= ___d; --i)
#define cmax(i, j) ((i) < (j) ? (i) = (j) : (i))
#define cmin(i, j) ((i) > (j) ? (i) = (j) : (i))
#define dmax(i, j) ((j) < (i) ? (i) : (j))
#define dmin(i, j) ((i) < (j) ? (i) : (j))
#define ddel(i, j) ((i) > (j) ? (i) - (j) : (j) - (i))
#define dabs(i) ((i) > 0 ? (i) : -(i))

#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace io
{
	const int MAXBUF = 1 << 22;
	char B[MAXBUF], *S = B, *T = B;
	#define getc() (S == T && (T = (S = B) + fread(B, 1, MAXBUF, stdin), S == T) ? 0 : *S++)
	template<class Type> inline Type read()
	{
		register Type aa = 0;
		register bool bb = 0;
		register char ch, *S = io::S, *T = io::T;
		for(ch = getc(); (ch < '0' || ch > '9') && ch != '-'; ch = getc())
			;
		for(ch == '-' ? bb = 1 : aa = ch - '0', ch = getc(); '0' <= ch && ch <= '9'; ch = getc())
			aa = aa * 10 + ch - '0';
		io::S = S, io::T = T;
		return bb ? -aa : aa; 
	}
	int (*F)() = read<int>;
	
	template<> inline double read()
	{
		register double aa, bb;
		register char ch;
		register char *S = io::S, *T = io::T;
		while(ch=getc(),(ch<'0'||ch>'9'))
			;aa=ch-'0';
		while(ch=getc(),(ch>='0'&&ch<='9'))aa=aa*10+ch-'0';
		if(ch=='.'){bb=1;while(ch=getc(),ch>='0'&&ch<='9')bb*=0.1,aa+=bb*(ch-'0');}
		io::S = S, io::T = T;
		return aa;
	}
	
	char buff[MAXBUF], *iter = buff;
	template<class T>inline void P(register T x, register char ch = '\n')
	{
		static int stack[110];
		register int O = 0;
		register char *iter = io::iter;
		if(!x)*iter++ = '0';
		else
		{
			(x < 0) ? x = -x, *iter++ = '-' : 1;
			for(; x; x /= 10)
				stack[++O] = x % 10;
			for(; O; *iter++ = '0' + stack[O--])
				;
		}
		*iter++ = ch, io::iter = iter;
	}
	
	inline void putc(register char ch) {*iter++ = ch;}
	
	inline void output() {fwrite(buff, 1, iter - buff, stdout), iter = buff;}
}


#include <ext/pb_ds/priority_queue.hpp>

namespace pb_ds
{
	using io::P;
	const int MAXN = 50010;
	const int MAXM = 100010;
	
	struct E {int x, y, a, b;} e[MAXM];
	#define rcs(A)  const A&
	inline bool cmp(rcs(E) a, rcs(E) b) {return a.a < b.a;}
	struct Data {int val, at;};
	#define dcho(x, y) ((x).val > (y).val ? (x) : (y))
	#define ccho(x, y) ((x).val < (y).val ? (x) = (y) : (x))
	struct Node; 
	Node *null;
	inline void swap( Node*& a,  Node*& b)
	{
		 Node* temp = a;
		a = b, b = temp;
	} 
	struct Node
	{
		Node *ch[2], *fa;
		Data cur, max;
		Node *top;
		bool flag;
		inline void rev()
		{
			flag ^= 1;
			swap(ch[0], ch[1]);
		}
		inline void push_down()
		{
			flag
			? 	ch[0]->rev(),
				ch[1]->rev(),
				flag = 0
			: 	0;
		}
		inline void push_up()
		{
			max = dcho(ch[0]->max, ch[1]->max);
			ccho(max, cur);
		}
		inline void rotate( bool f)
		{
			 Node *y = fa;
			top = y->top;
			y->push_down(), push_down();
			(fa = y->fa)->ch[y->fa->ch[1] == y] = this; 
			(y->ch[f] = ch[!f])->fa = y;
			(ch[!f] = y)->fa = this;
			y->push_up();
		}
		inline void splay()
		{
			 Node *y = fa;
			 bool f;
			for(push_down(); y != null; y = fa)
				if(y->fa == null) rotate(y->ch[1] == this);
				else
				{
					(f = y->ch[1] == this) == (y->fa->ch[1] == y)
					? (y->rotate(f), rotate(f))
					: (rotate(f), rotate(!f));
				}
			push_up();
		}
		inline void expose( Node *p = null)
		{
			splay();
			if(ch[1] != null)
			{
				ch[1]->top = this,
				ch[1]->fa = null;
			}
			(ch[1] = p)->fa = this;
			push_up();
		}
	}pos[MAXN + MAXM];
	
	inline void init() {null = pos;}
	
	inline Node* access( Node* x)
	{
		for(x->expose(); x->top; x = x->top)
			x->top->expose(x);
		return x;
	}
	
	inline void link( Node* x,  Node* y)
	{
///*lgg*/printf("link %ld ~ %ld\n", x - pos, y - pos);
		(x = access(x))->rev();
		x->top = y;
	}
	inline void cut( Node* x,  Node* y)
	{
///*lgg*/printf("cut %ld ~ %ld\n", x - pos, y - pos);
		x->expose(), y->expose();
		if(x->top == y) x->top = NULL;
		else y->top = NULL;
	}
	
	struct Result {bool first; Data second;};
	Data empty = (Data) {0, 0};
	inline Result check( Node* x,  Node* y)
	{
///*lgg*/printf("check %ld ~ %ld\n", x - pos, y - pos);
		access(x);
		 Data res = empty;
		 Node *A = access(y);
		if(A->ch[1] != null)
			ccho(res, A->ch[1]->max);
		 Node *B = access(x);
		if(A != B) return (Result) {0, res};
///*lgg*/puts("connected");
		if(A->ch[1] != null)
			ccho(res, A->ch[1]->max);
		return (Result) {1, dcho(res, A->cur)};			 
	}
	
	inline void main()
	{
		 int (*F)() = io::read<int>;
		init();
		 int n = F(), m = F(), x, y;
		for( int i = 1; i <= m; ++i)
		{
			e[i] = (E) {x = F(), y = F(), F(), F()};
			if(x == y) --i, --m;
		}
		std::sort(e + 1, e + m + 1, cmp);
		For(i, 0, n)
			pos[i] = (Node) {{null, null}, null};
		 int ans = 1 << 30, t;
		 Node* cur;
		Result res;
		 Node *pos = pb_ds::pos, *edge = pos + n;
		For(i, 1, m)
		{
			if(e[i].a >= ans) break;
			x = e[i].x, y = e[i].y;
			*(cur = edge + i) = (Node) {{null, null}, null, (Data) {e[i].b, i}};
			res = check(pos + x, pos + y);
			if(res.first)
			{
				if(res.second.val > e[i].b)
				{
					t = res.second.at;
					cut(pos + e[t].x, edge + t);
					cut(pos + e[t].y, edge + t);
					link(cur, pos + x);
					link(cur, pos + y);
				}
			}
			else
			{
				link(cur, pos + x);
				link(cur, pos + y);
			}
			if(e[i].a != e[i + 1].a)
			{
				if((res = check(pos + 1, pos + n)).first)
					cmin(ans, e[i].a + res.second.val);
			}
///*lgg*/printf("add %d %d %d %d ans = %d\n", e[i].x, e[i].y, e[i].a, e[i].b, ans);
		}
		P((ans < (1 << 30)) ? ans : -1);
	}
}

int main()
{
	pb_ds::main();
	io::output();
}
