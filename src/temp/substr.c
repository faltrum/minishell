#include <stdlib.h>
#include <string.h>

static size_t	bcal(char const* s, size_t start, size_t len)
{
	size_t	slen;

	if (s == 0)
		return (0);
	start++;
	slen = strlen(s);
	if (start > slen)
		return (0);
	if (len > slen - start)
		return (slen - start + 1);
	return (len);
}

char    *ft_substr(char const* s, unsigned int start, size_t len)
{
	char* str;
	size_t	first;
	size_t	ind;

	first = (size_t)start;
	len = bcal(s, first, len);
	str = (char*)malloc(len + 1);
	if (str == 0 || s == 0)
		return (0);
	ind = 0;
	while (ind < len && s[first + ind] != 0)
	{
		str[ind] = s[first + ind];
		ind++;
	}
	str[ind] = 0;
	return (str);
}
