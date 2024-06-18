#include "minishell.h"

int	export_error(char *identifier)
{
	char msg[500];

	ft_strlcat(msg, EXPORT, 500);
	ft_strlcat(msg, ": `", 500);
	ft_strlcat(msg, identifier, 500);
	ft_strlcat(msg, "': ", 500);
	ft_strlcat(msg, ERR_VALID_IDENTIFIER, 500);
	return (ft_err(-1, msg, 0, 0));
}
