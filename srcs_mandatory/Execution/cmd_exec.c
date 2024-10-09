/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:16:21 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 17:22:12 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec_error(void)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		exit(127);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("Error: Permission denied\n", 2);
		exit(126);
	}
	else
		exit(1);
}

void	cmd_exec(t_ms *ms, char *cmd)
{
	char	**cmds;

	cmds = ms->p->cmds;
	if (!cmds)
		return ;
	cmd = cmd_path(ms->p->envi, cmds[0]);
	if (cmd)
	{
		execve(cmd, cmds, ms->p->envi);
		ft_free_tab(cmds);
		free(cmd);
		handle_exec_error();
	}
	else
	{
		ft_putstr_fd("Error : command not found\n", 2);
		ft_free_tab(cmds);
		exit(127);
	}
}
