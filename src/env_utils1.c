/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:03 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/05 07:20:52 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(void *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (lst != NULL)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast_env(*lst);
			new->prev = temp;
			temp->next = new;
		}
	}
}

void	save_env(t_var *var, char **env)
{
	int		i;
	int		eq_ind;
	t_env	*new;

	i = 0;
	var->env = NULL;
	while (env[i])
	{
		eq_ind = ft_strchr_index(env[i], '=');
		new = ft_lstnew_env(ft_substr(env[i], 0, eq_ind), ft_substr(env[i], eq_ind + 1, ft_strlen(env[i]))); // Y si falla?
		ft_lstadd_back_env(&var->env, new);
		i++;
	}
}
