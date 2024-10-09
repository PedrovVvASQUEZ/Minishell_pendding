/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:27:21 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 17:54:57 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_infile(t_token *tok)
{
	t_token	*current;

	current = tok;
	while (current)
	{
		if (current->type == INFILE)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

char	*find_outfile(t_token *tok)
{
	t_token	*current;

	current = tok;
	while (current)
	{
		if (current->type == OUTFILE)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

void	exec_cleaner(t_ms *ms)
{
	free(ms->p->infile);
	free(ms->p->outfile);
	ft_free_tab(ms->p->cmds);
	ft_free_tab(ms->p->envi);
	free(ms->p->pid);
	close(ms->p->pipefd[0]);
	close(ms->p->pipefd[1]);
}
