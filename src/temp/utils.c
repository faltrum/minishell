#include "../../includes/Header.h"

int	wordchar(char c)
{
	if (isalnum(c) || c == '$' || c == '_')
		return (1);
	return (0);
}