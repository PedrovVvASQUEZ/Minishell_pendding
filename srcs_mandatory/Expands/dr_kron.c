/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_kron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:02:28 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/03 18:39:36 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	j = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	finishing(t_token *tok)
{
	while (tok)
	{
		remove_quotes(tok->value);
		tok = tok->next;
	}
}

char	*process_token_value(t_token *tok,
			t_env *env, int v_return, char *fs)
{
	t_var	v;

	init_var(&v);
	while (tok->value[v.x])
	{
		if (tok->value[v.x] == '$' && tok->value[v.x + 1])
		{
			if (tok->value[v.x + 1] == '$')
				fs = double_dollar(fs, &v.x);
			else if (tok->value[v.x + 1] == '?' && expandable(tok->value, v.x))
				fs = dollar_bruh(fs, &v.x, v_return);
			else if (expandable(tok->value, v.x))
				fs = expand_variable(tok, env, &v.x, fs);
			else
				fs[v.y++] = tok->value[v.x++];
		}
		else
			fs[v.y++] = tok->value[v.x++];
		if (!fs)
			return (NULL);
		v.y = ft_strlen(fs);
	}
	fs[v.y] = '\0';
	return (fs);
}

char	*transformer(t_token *tok, char *fs)
{
	if (!tok || !fs)
		return (NULL);
	if (tok->value)
		free(tok->value);
	tok->value = ft_strdup(fs);
	if (!tok->value)
	{
		free(fs);
		return (NULL);
	}
	free(fs);
	return (tok->value);
}

void	dr_kron(t_token *tok, t_env *env, int v_return)
{
	char	*fs;

	if (!tok || !env || !tok->value || !env->value)
		return ;
	fs = malloc_calculator(tok, env, v_return);
	if (!fs)
		return ;
	fs = process_token_value(tok, env, v_return, fs);
	if (!fs)
		return ;
	transformer(tok, fs);
}
