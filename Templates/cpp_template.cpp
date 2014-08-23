#pragma comment(linker, "/STACK:10240000")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Foru(i, a, b) for(int i = (a); i < (b); ++i)

using namespace std;

typedef long long LL;
typedef pair<int, int> pii;

const int INF = 1000000000;

#ifdef MAX_BUFFER

namespace BufferedReader {

	char buff[MAX_BUFFER + 5], *ptr = buff, c;
	bool flag;

	inline bool nextChar(char &c) {
		if ( (c = *ptr++) == 0 ) {
			int tmp = fread(buff, 1, MAX_BUFFER, stdin);
			buff[tmp] = 0;
			if (tmp == 0)
				return false;
			ptr = buff;
			c = *ptr++;
		}
		return true;
	}

	inline bool nextUnsignedInt(unsigned int &x) {
		for ( ; ; ) {
			if ( !nextChar(c) )
				return false;
			if ('0' <= c && c <= '9') break;
		}
		x = c - '0';
		for ( ; ; ) {
			if ( !nextChar(c) )
				break;
			if (c < '0' || c > '9') break;
			x = x * 10 + c - '0';
		}
		return true;
	}

	inline bool nextInt(int &x) {
		for ( ; ; ) {
			if ( !nextChar(c) )
				return false;
			if (c == '-' || ('0' <= c && c <= '9'))
				break;
		}
		if (c == '-') {
			x = 0;
			flag = true;
		}
		else {
			x = c - '0';
			flag = false;
		}
		for ( ; ; ) {
			if ( !nextChar(c) )
				break;
			if (c < '0' || c > '9') break;
			x = x * 10 + c - '0';
		}
		if (flag) x = -x;
		return true;
	}

};
#endif

int main() {
	return 0;
}
