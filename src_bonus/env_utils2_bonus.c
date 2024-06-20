/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:41:32 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_env	*find_in_env(t_env *lst, char *name)
{
	t_env	*tmp;

	tmp = lst;
	while (lst && tmp && name)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_lstdelone_env(t_env **lst, t_env *todelate)
{
	if (!lst || !*lst || !todelate)
		return ;
	if (todelate == *lst)
	{
		*lst = todelate->next;
		if (*lst)
			(*lst)->prev = NULL;
	}
	else
	{
		todelate->prev->next = todelate->next;
		if (todelate->next)
			todelate->next->prev = todelate->prev;
	}
	free(todelate->name);
	free(todelate->value);
	free(todelate);
}

void	add_in_env(t_var *var, char *name, char *value)
{
	t_env	*new;

	new = ft_lstnew_env(name, value);
	if (new)
		ft_lstadd_back_env(&var->env, new);
	else
	{
		free(name);
		free(value);
	}
}

void	replace_or_set_env(t_var *var, char *name, char *value)
{
	t_env	*node;

	node = find_in_env(var->env, name);
	if (!node)
	{
		if (value)
			add_in_env(var, ft_strdup(name), ft_strdup(value));
		else
			add_in_env(var, ft_strdup(name), NULL);
		node = find_in_env(var->env, name);
		if (node && (!node->name || !node->value))
			ft_err(0, ERR_MALLOC, 0, 0);
	}
	else
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			ft_err(0, ERR_MALLOC, 0, 0);
	}
}
