/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:12:06 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 18:23:22 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executioner(t_ms *ms)
{
	int	returnv;
	int	x;

	returnv = 0;
	x = 0;
	while (x < ms->p->cmd_count)
	{
		pipe(ms->p->pipefd);
		ms->p->pid[x] = fork();
		if (ms->p->pid[x] == -1)
			exit(1);
		if (ms->p->pid[x] == 0)
			child_process(ms, x);
		else
		{
			close(ms->p->pipefd[1]);
			if (x > 0)
				close(ms->p->previousfd);
			ms->p->previousfd = ms->p->pipefd[0];
		}
		x++;
	}
	returnv = wait_da_boy(ms->p);
	return (returnv);
}

int	executor(t_ms *ms)
{
	if (ms->tokens && ms->tokens->type == CMD && ms->p->cmd_count == 1
		&& strcmp(ms->tokens->value, "unset") == 0)
	{
		ft_unset(ms->tokens, ms->env);
		return (0);
	}
	else
	{
		ms->p->pid = ft_calloc(ms->p->cmd_count, sizeof(int));
		if (!ms->p->pid)
		{
			ft_putstr_fd("Malloc failed", 2);
			return (1);
		}
		init_pipe(ms);
		ms->v_return = executioner(ms);
		exec_cleaner(ms);
		return (ms->v_return);
	}
}

// int	the_execution(t_ms *ms)
// {
// 	while (ms->tokens)
// 	{
		
// 	}
// }
