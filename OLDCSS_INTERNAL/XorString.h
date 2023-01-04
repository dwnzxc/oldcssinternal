#ifndef __XORSTRING__
#define __XORSTRING__

template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
public:
	char s[BUFLEN];

	explicit XorStr(const char* xs);
	~XorStr() { for (int i = 0;i<BUFLEN;i++)s[i] = 0; }
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char* xorstring)
{
	int xvalue = XORSTART;
	int i = 0;
	for (;i < (BUFLEN - 1);i++)
	{
		s[i] = xorstring[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}

#endif