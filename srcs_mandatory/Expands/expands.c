/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:08:24 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/03 16:39:09 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_dollar(char *fs, int *x)
{
	char	*new_fs;
	char	*tmp;

	tmp = ft_strjoin(fs, "$$");
	if (!tmp)
		return (NULL);
	new_fs = ft_strdup(tmp);
	free(tmp);
	if (!new_fs)
		return (NULL);
	*x += 2;
	return (new_fs);
}

char	*dollar_bruh(char *fs, int *x, int v_return)
{
	char	*v_return_str;
	char	*new_fs;
	char	*tmp;

	v_return_str = ft_itoa(v_return);
	if (!v_return_str)
		return (NULL);
	tmp = ft_strjoin(fs, v_return_str);
	free(v_return_str);
	if (!tmp)
		return (NULL);
	new_fs = ft_strdup(tmp);
	if (!new_fs)
		return (NULL);
	free(tmp);
	*x += 2;
	return (new_fs);
}

char	*expand_variable(t_token *tok, t_env *env, int *x, char *fs)
{
	char	*var_name;
	t_env	*ev;
	char	*var_value;
	char	*tmp;
	char	*new_fs;

	var_name = tracker(tok->value, x);
	if (!var_name)
		return (NULL);
	ev = find_node(var_name, env);
	free(var_name);
	if (!ev || !ev->value)
		return (fs);
	var_value = ev->value;
	tmp = ft_strjoin(fs, var_value);
	if (!tmp)
		return (NULL);
	new_fs = ft_strdup(tmp);
	free(tmp);
	if (!new_fs)
		return (NULL);
	return (new_fs);
}

// char	*expand_env_value(char *fs, char *env_value, int *x, char *tok_value)
// {
// 	char	*tmp;

// 	if (!fs || !env_value || !x || !tok_value)
// 		return (NULL);
// 	tmp = ft_strjoin(fs, env_value);
// 	if (!tmp)
// 		return (free(fs), NULL);
// 	return (tmp);
// }

// char	*expand_variable(t_token *tok, t_env *env, int *x, char *fs)
// {
// 	t_env	*ev;
// 	char	*tmp;

// 	tmp = tracker(tok->value, x);
// 	if (!tmp)
// 		return (free(fs), NULL);
// 	ev = find_node(tmp, env);
// 	free(tmp);
// 	if (!ev)
// 		return (fs);
// 	return (expand_env_value(fs, ev->value, x, tok->value));
// }

/********************************************************************/

// Entre double quote -> remplacement

// Entre single quote -> pas de remplacement

// $EXPAND doit etre suivi d'un espace pour etre remplace

// $$ -> NULL

// Malloc la nouvelle chaine moins les quotes

// $? -> renvoi la valeur de retour (A gerer a part
// 			des variables d'environnement)avec EXIT_STATUS
/********************************************************************/

// char	*dr_kron(t_token *tok, t_env *env, int v_return)
// {
// 	t_env	*ev;
// 	char	*fs;
// 	char	*tmp;
// 	int		x;
// 	int		y;

// 	if (!tok || !env || !tok->value || !env->value)
// 		return (NULL);
// 	x = 0;
// 	y = 0;
// 	fs = ft_calloc(1, sizeof(char) * ft_strlen(tok->value) + 1);
// 	if (!fs)
// 		return (NULL);
// 	printf("Debug: fs after calloc: %s\n", fs);
// 	while (tok->value[x])
// 	{
// 		if (tok->value[x] == '$' && tok->value[x + 1] == '?')
// 		{
// 			fs = dollar_bruh(fs, &x, v_return);
// 			if (!fs)
// 				return (NULL);
// 			y = ft_strlen(fs);
// 		}
// 		if (tok->value[x] == '$' && expandable(tok->value, &x))
// 		{
// 			tmp = tracker(tok->value, &x);
// 			if (!tmp)
// 				return (free(fs), NULL);
// 			printf("Debug: tracker returned %s\n", tmp);
// 			ev = find_node(tmp, env);
// 			free(tmp);
// 			if (!ev)
// 				continue ;
// 			printf("name: \033[0;36m %-20s \033[0m |\t
// 				value: \033[0;35m %-18s \033[0m \n%d",
// 				ev->name, ev->value, ev->equal_sign);
// 			printf("--------------------------------------------------\n");
// 			fs = expand_env_value(fs, ev->value, &x, tok->value);
// 			printf("Debug: fs after expand_env_value: %s\n", fs);
// 			y = ft_strlen(fs);
// 		}
// 		else
// 		{
// 			fs[y++] = tok->value[x++];
// 			printf("Debug: y incremented to: %d\n", y);
// 		}
// 	}
// 	fs[y] = '\0';
// 	printf("Debug: y incremented to: %d\n", y);
// 	printf("Debug: final fs: %s\n", fs);
// 	return (transformer(tok, fs));
// }
