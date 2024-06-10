/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:57 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/18 19:00:43 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expansion(t_var *var, char *command)
{
	int		i;
	int		len;
	int		last;
	char	*name;
	char	*value_str;
	t_env	*env;
	int		index;

	i = 0;
	len = 0;
	last = 0;
	name = NULL;
	value_str = NULL;
	while (last >= 0)
	{
		i = ft_strchr_index(&command[last], '$');
		if (i != -1)
		{
			i += last + 1;
			while (command[i] && ft_isalnum(command[i]))
			{
				i++;
				len++;
			}
		}
		if (len == 0)
			last = -1;
		else
		{
			name = malloc(sizeof(char) * len + 1);
			if (!name)
				return (NULL);
			ft_strlcpy(name, &command[i - len], len + 1);
			env = find_in_env(var->env, name);
			free(name);
			if (env)
				value_str = ft_strdup(env->value);
			else if (!ft_isalpha(command[ft_strchr_index(&command[last],
							'$') + 1]))
			{
				index = ft_strchr_index(&command[last], '$') + 2;
				value_str = ft_substr(command, index, len - 1);
			}
			command = ft_replace_strstr(command, i - len - 1, len, value_str);
			last = i - ft_strlen(value_str);
			free(value_str);
			value_str = "";
		}
		len = 0;
	}
	return (command);
}

void	remove_quote(char **str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = '\0';
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			c = (*str)[i++];
		else
			(*str)[j++] = (*str)[i];
		while (c && (*str)[i])
		{
			if ((*str)[i] == c)
				break ;
			(*str)[j++] = (*str)[i++];
		}
		if (!(*str)[i] && c)
		{
			(*str) = NULL;
			break ;
		}
		c = '\0';
		i++;
	}
	if (*str)
		(*str)[j] = '\0';
}

void	recursive_tree(t_var *var, t_info_tree *tree, char *string)
{
	int	j;

	if (string == NULL || tree == NULL)
		return ;
	j = get_biggest_priority(string);
	if (j == -1)
	{
		tree->left = NULL;
		tree->right = NULL;
		tree->operator = NULL;
		tree->command = string;
		remove_quote(&tree->command);
	}
	else
	{
		tree->command = NULL;
		tree->operator = get_operator(string, j);
		tree->left = init_linked_tree(save_sentence_l(string, j),
				tree->operator, tree->operator);
		tree->right = init_linked_tree(save_sentence_r(string, j),
				tree->operator, tree->operator);
		check_operator(tree);
		remove_quote(&tree->command);
		recursive_tree(var, tree->left, tree->left->command);
		recursive_tree(var, tree->right, tree->right->command);
	}
}

void	recursive2(t_var *var, t_info_tree *tree)
{
	int	copia_0;
	int	copia_1;

	copia_0 = dup(0);
	copia_1 = dup(1);
	if (tree->operator != NULL)
		function_ptr_op(var, tree);
	if (tree->left != NULL && tree->left->left != NULL)
		recursive2(var, tree->left);
	if (tree->operator == NULL)
		func_pipe(var, tree->command);
	if (tree->right != NULL && tree->right->left != NULL)
		recursive2(var, tree->right);
	dup2(copia_0, 0);
	dup2(copia_1, 1);
}

void	make_binnary_tree(t_var *var, char *line)
{
	t_info_tree	*tmp;

	tmp = init_struct_tree();
	var->tree = tmp;
	line = expansion(var, line);
	recursive_tree(var, tmp, line);
	tmp = var->tree;
	recursive2(var, tmp);
	tmp = var->tree;
	free_binnarytree(tmp);
}