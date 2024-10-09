/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_da_boy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:12:44 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 14:01:00 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_da_boy(t_pipe *p)
{
	int	x;
	int	status;
	int	*exit_status;

	exit_status = malloc(p->cmd_count * sizeof(int));
	if (!exit_status)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (-1);
	}
	x = 0;
	while (x < p->cmd_count)
	{
		if (ft_strncmp(p->cmds[x], "sleep", 5) == 0)
			wait(&status);
		else
			waitpid(p->pid[x], &status, 0);
		exit_status[x] = status >> 8;
		x++;
	}
	status = exit_status[p->cmd_count - 1];
	free(exit_status);
	return (status);
}
