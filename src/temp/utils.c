#include "../../includes/Header.h"

int	wordchar(char c)
{
	if (isalnum(c) || c == '$' || c == '_' || c == '.' || c == '/')
		return (1);
	return (0);
}