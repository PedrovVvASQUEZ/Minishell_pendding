/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:44:34 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 17:26:34 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_opener(t_ms *ms, int i_o)
{
	if (i_o == 0)
	{
		ms->p->fd_in = open(ms->p->infile, O_RDONLY);
		if (ms->p->fd_in < 0)
		{
			perror(ms->p->infile);
			exit(1);
		}
		dup2(ms->p->fd_in, STDIN_FILENO);
		close(ms->p->fd_in);
	}
	else if (i_o == ms->p->cmd_count - 1)
	{
		ms->p->fd_out = open(ms->p->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ms->p->fd_out < 0)
		{
			perror(ms->p->outfile);
			exit(1);
		}
		dup2(ms->p->fd_out, STDOUT_FILENO);
		close(ms->p->fd_out);
	}
}
