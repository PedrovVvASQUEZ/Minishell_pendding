/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:33:14 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 17:37:26 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_ms *ms, int x)
{
	free(ms->p->pid);
	redirector(ms, x);
	if (x == 0 || x == ms->p->cmd_count - 1)
		file_opener(ms, x);
	cmd_exec(ms, ms->p->cmds[x]);
	exit(127);
}
