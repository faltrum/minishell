/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:03 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/18 22:08:20 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(void *name, char *value)
{
	t_env	*node;

	if (ft_errloc(sizeof(*node), 1, (void **) &node) == -1)
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

static int	shlvl_error(int lvl)
{
	char	msg[500];

	msg[0] = 0;
	ft_strlcat(msg, "warning: shell level ", 500);
	ft_strlcat(msg, "(", 500);
	ft_strlcat(msg, ft_itoa(lvl), 500);
	ft_strlcat(msg, ")", 500);
	ft_strlcat(msg, " too high, resetting to 1", 500);
	return (ft_err(1, msg, 0, 0));
}
void	update_shlvl(t_var *var)
{
	char	*new;
	t_env	*env;
	int		lvl;

	env = find_in_env(var->env, "SHLVL");
	if (env && env->value)
	{
		lvl = ft_atoi(env->value) + 1;
		if (lvl > 1000)
			lvl = shlvl_error(lvl);
		else if (lvl < 0)
			lvl = 0;
		new = ft_itoa(lvl);
		if (new)
		{
			free(env->value);
			env->value = new;
		}
		else
			ft_err(0, ERR_MALLOC, "SHLVL UPDATE", 0);
	}
	else
		add_in_env(var, ft_strdup("SHLVL"), ft_strdup("1"));
}
