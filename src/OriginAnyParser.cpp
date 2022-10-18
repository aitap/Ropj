#ifdef _WIN32
	// MinGW compiler warns on the use of C++11 time formats %F and %T,
	// despite UCRT supporting them. There's only one such call in
	// liborigin, and we never perform it. Inistead of patching the
	// source code, which resides in the upstream repo, let's patch the
	// call out using the preprocessor.
	#include <ctime> // process declarations before redefining symbol
	#define strftime(s, n, f, t) // remove the call
#endif
#include "liborigin/OriginAnyParser.cpp"
