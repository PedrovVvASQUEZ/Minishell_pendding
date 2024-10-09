/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:40:01 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 13:59:26 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_the_path(char **pathsss, char *cmd)
{
	int		x;
	char	*path;
	char	*tmp;

	x = 0;
	while (pathsss[x])
	{
		path = ft_strjoin(pathsss[x], "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_tab(pathsss);
			return (path);
		}
		free(path);
		x++;
	}
	ft_free_tab(pathsss);
	return (NULL);
}

char	*cmd_path(char **envi, char *cmd)
{
	int		x;
	char	*path;
	char	**pathsss;

	x = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (envi[x])
	{
		if (ft_strncmp(envi[x], "PATH=", 5) == 0)
		{
			path = ft_strdup(envi[x] + 5);
			pathsss = ft_split(path, ':');
			free(path);
			path = get_the_path(pathsss, cmd);
			if (path)
				return (path);
		}
		x++;
	}
	return (NULL);
}
