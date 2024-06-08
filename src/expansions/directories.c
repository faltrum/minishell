#include "minishell.h"

void	sort_directories(t_word_list *directories)
{
	t_word_list	*node;
	t_word_list	*head;
	char		*aux;

	head = directories;
	while (directories)
	{
		node = head;
		while (node->next)
		{
			if (ft_strcmp(node->word, node->next->word) > 0)
			{
				aux = node->word;
				node->word = node->next->word;
				node->next->word = aux;
			}
			node = node->next;
		}
		directories = directories->next;
	}
}

// Error checking  //


int	get_directories(t_word_list **directories)
{
	DIR				*stream;
	char			cwd[PATH_MAX];
	struct dirent	*dir;
	t_word_list		*node;

	getcwd(cwd, sizeof(cwd));
	stream = opendir(cwd);
	dir = readdir(stream);
	while (dir)
	{
		if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
		{
			node = allocate_last_node(directories);
			node->word = ft_strdup(dir->d_name);
		}
		dir = readdir(stream);
	}
	closedir(stream);
	sort_directories(*directories);
	return (0);
}
