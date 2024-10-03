/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:44:40 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/03 15:13:24 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_ms *ms)
{
	t_token	*current;

	if (!ms || !ms->tokens)
		return ;
	current = ms->tokens;
	while (current)
	{
		if (current->value)
		{
			dr_kron(current, ms->env, ms->v_return);
			finishing(current);
			// display_tokens(current);
		}
		current = current->next;
	}
}
