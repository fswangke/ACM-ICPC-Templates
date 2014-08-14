
#include <ext/rope>

using __gnu_cxx::crope;
using __gnu_cxx::rope;

a = b.substr(from, len);		// [from, from + len)
a = b.substr(from);				// [from, from]
a = b.c_str();					// quite slow and might lead to memory leaks
a.insert(p, str);				// insert str before position p
a.erase(i, n);					// erase [i, i + n)
