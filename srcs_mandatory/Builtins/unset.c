/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:27:28 by acarpent          #+#    #+#             */
/*   Updated: 2024/10/09 15:48:56 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_env *env, t_env *node_to_del)
{
	node_to_del = env;
	if (node_to_del)
	{
		if (env->prev)
			env->prev->next = env->next;
		if (env->next)
			env->next->prev = env->prev;
		free(env->name);
		free(env->value);
		free(env);
	}
}

void	ft_unset(t_token *tok, t_env *env)
{
	int		i;
	t_env	*node_to_del;

	i = 0;
	node_to_del = NULL;
	if (tok->next)
	{
		tok = tok->next;
		while (env)
		{
			if (ft_strcmp(env->name, tok->value) == 0)
			{
				del_node(env, node_to_del);
				break ;
			}
			env = env->next;
		}
	}
}
