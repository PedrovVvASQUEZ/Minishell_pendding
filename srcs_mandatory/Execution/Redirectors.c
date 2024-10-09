/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:58:05 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 16:44:20 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirector(t_ms *ms, int x)
{
	if (x != 0)
	{
		dup2(ms->p->previousfd, STDIN_FILENO);
		close(ms->p->previousfd);
	}
	if (x != ms->p->cmd_count - 1)
		dup2(ms->p->pipefd[1], STDOUT_FILENO);
	close(ms->p->pipefd[0]);
	close(ms->p->pipefd[1]);
}
