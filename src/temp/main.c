#include "../../includes/Header.h"

void    print_args(t_word_list *words) 
{
    printf("Argumentos: ");
    if (!words) {
        printf("No args ");
        return;
    }
    while(words)
	{
		printf(" %s ", words->word);
		words = words->next;
	}
    printf("\n");
}

void    print_red(t_redirect *reds) 
{
    printf("Redirecciones: ");
	if (!reds)
		printf("No redirs ");
    while (reds)
    {
        printf("file: %s ", reds->word);
        printf("type: %d ", reds->type);
        reds = reds->next;
    }
    printf("\n");

}

void    printf_commands(t_command *node) {
    printf("Command: ");
    switch (node->type) {
    case cm_connection:
            printf("Type: connection \n" );
            printf("First: ");
            printf_commands(node->value.connection->first);
            printf("Second: ");
            printf_commands(node->value.connection->second);
            break;
    case cm_simple:
            printf("Type: simple ");
            print_args(node->value.simple->words);
            print_red(node->value.simple->redirects);
    }
}

t_command	*temp_name_additions(char *str)
{
    t_command	*head;
	char		*ls;

	if (!str)
		return (NULL);

	ls = ft_strchr(str, '\n');
	if (ls)
		*ls = 0;

	if (*str == 0)
		return (NULL);

    head = parse_list(str);

    if (head == NULL)
        printf("Invalid syntax or error (debug) \n");

    return (head);
}