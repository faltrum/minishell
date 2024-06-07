#include "minishell.h"

void	hide_quote(char *word, int i[4], int *flags)
{
	int j;

	j = i[0];
	if ((*flags & QUOTED && word[j] == '"') || (*flags & DQUOTED && word[j] == '\''))
	{
		advance_one(word, &i[0], &i[2], flags);
		return ;
	}
	if (word[j] == '\'')
		(*flags) ^= QUOTED;
	else if (word[j] == '"')
		(*flags) ^= DQUOTED;
	word[j] = -1;
}

void	advance_one(char *word, int *i, int *exp_len, int *flags)
{
	if (word[*i])
	{
		(*i)++;
		if (*exp_len == 1)
			(*flags) = *flags & ~EXPANDED;
		if (*exp_len > 0)
			(*exp_len)--;
	}
}
