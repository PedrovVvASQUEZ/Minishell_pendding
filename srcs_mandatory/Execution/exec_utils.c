/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:50:48 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/09 17:51:24 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_counter(t_env *env)
{
	t_env	*current;
	int		x;

	x = 0;
	current = env;
	while (current)
	{
		x += 1;
		current = current->next;
	}
	return (x);
}

int	cmd_counter(t_token *tok)
{
	t_token	*current;
	int		x;

	x = 0;
	current = tok;
	while (current)
	{
		if (tok->type == CMD)
			x += 1;
		current = current->next;
	}
	return (x);
}

char	**the_env(t_env *env)
{
	char	**envi;
	int		y;

	y = 0;
	envi = ft_calloc(env_counter(env), sizeof(char *));
	if (!envi)
		return (NULL);
	while (env)
	{
		if (env->equal_sign == 1)
			envi[y] = ft_strjoin_equal(env->name, env->value);
		else
			envi[y] = ft_strdup(env->name);
		env = env->next;
	}
	return (envi);
}

char	**the_tokens(t_token *tok)
{
	char	**toks;
	int		y;

	y = 0;
	toks = ft_calloc(token_counter(tok), sizeof(char *));
	if (!toks)
		return (NULL);
	while (tok)
	{
		toks[y] = ft_strdup(tok->value);
		tok = tok->next;
	}
	return (toks);
}

void	init_pipe(t_ms *ms)
{
	ms->p = (t_pipe *)malloc(sizeof(t_pipe));
	if (!ms->p)
	{
		free(ms);
		return ;
	}
	ms->p->pid = NULL;
	ms->p->cmd_count = cmd_counter(ms->tokens);
	ms->p->previousfd = 0;
	ms->p->cmds = the_tokens(ms->tokens);
	if (!ms->p->cmds)
		ms->p->cmds = NULL;
	ms->p->envi = the_env(ms->env);
	if (!ms->p->envi)
		ms->p->envi = NULL;
	ms->p->infile = find_infile(ms->tokens);
	if (!ms->p->infile)
		ms->p->infile = NULL;
	printf("%s\n", ms->p->infile);
	ms->p->outfile = find_outfile(ms->tokens);
	if (!ms->p->outfile)
		ms->p->outfile = NULL;
	printf("%s\n", ms->p->outfile);
	ms->p->fd_in = 0;
	ms->p->fd_out = 0;
	ms->p->here_doc_fd = 0 ;
}
