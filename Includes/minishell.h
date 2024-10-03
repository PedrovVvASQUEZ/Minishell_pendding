/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:22:22 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/03 18:15:24 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/***********************/
/*  LIBRARIES IMPORTS  */
/***********************/

# include "../Libraries/pedro_lib/pedro_lib.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

/************************/
/*       DEFINES        */
/************************/

# define PROMPT_LINE "\1\033[1;91m\2MYSHELL=> \1\033[0m\2"

/************************/
/*       SIGNALS        */
/************************/

# define CTRL_C 130
# define CTRL_D 0
# define CTRL_BS 131

/************************/
/*    GLOBAL VARIABLE   */
/************************/

// extern int	g_var;

/************************/
/*      STRUCTURES      */
/************************/


typedef struct s_exp
{
	size_t	x;
	bool	in_single_quote;
	bool	in_double_quote;
}				t_exp;

typedef enum s_token_type
{
	CMD,
	ARG,
	WORD,
	PIPE,
	INFILE,
	OUTFILE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	LIMITER,
}				t_token_type;

typedef struct s_pipe
{
	pid_t		pipefd[2];
	int			*pid;
	int			cmd_count;
	int			previousfd;
	char		**cmds;
	char		**envi;
	char		*infile;
	char		*outfile;
	int			fd_in;
	int			fd_out;
}				t_pipe;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				equal_sign;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;


typedef struct s_ms
{
	char	*prompt;
	t_env	*env;
	t_token	*tokens;
	t_pipe	*p;
	int		v_return;
	int		t_count;
}				t_ms;

typedef struct s_var
{
	int		x;
	size_t	y;
}				t_var;

/************************/
/*	    PROTOTYPES	    */
/************************/

//MINISHELL

// The program

t_ms			*init_ms(void);
t_ms			*init_program(char **env);
char			*prompt(t_ms *ms);
void			the_program(t_ms *ms);

// Visualiser

void			display_tokens(t_token *tokens);
void			display_envi(t_env *env);

// pre_parser functions

bool			q_check(char *s);
bool			is_quoted(char *s, int index);
bool			c_check(char *s);
bool			shit_check_1(char *s);
bool			full_check(char *s);

// Env funtions

t_env			*find_lastv(t_env *env);
int				find_equal_sign(char *s);
// char			*transformed(char *var);
void			add_env(t_env **tok, char *value);
t_env			*init_env(char **env);
void			delete_env(t_env **head, t_env *node_to_del);
void			free_env(t_env **head);

// lexer functions

bool			is_separator(char c, char next_c);
bool			is_quote(char c);
bool			is_space(char c);
t_token			*find_last(t_token *tok);
// int				token_len(t_token *tok);
t_token			*init_token(char *value);
void			add_token(t_token **tok, char *value);
t_token_type	da_tok(char *s, t_token *previous);
t_token			*lexer(char *input);
void			delete_token(t_token **head, t_token *node_to_del);
void			free_tokens(t_token **head);

// Expander functions

void			init_var(t_var *v);	
char			*malloc_calculator(t_token *tok, t_env *env, int v_return);
char			*tracker(char *s, int *x);
char			*transformer(t_token *tok, char *fs);
char			*expand_env_value(char *fs, char *env_value,
					int *x, char *tok_value);
char			*double_dollar(char *fs, int *x);
char			*dollar_bruh(char *fs, int *x, int v_return);
bool			expandable(const char *str, size_t pos);
t_env			*find_node(char *s, t_env *env);
char			*expand_variable(t_token *tok, t_env *env, int *x, char *fs);
char			*process_token_value(t_token *tok,
					t_env *env, int v_return, char *fs);
void			dr_kron(t_token *tok, t_env *env, int v_return);
void			finishing(t_token *tok);
void			remove_quotes(char *str);
void			expander(t_ms *ms);

//PIPEX
char			*cmd_path(char **envi, char *cmd);
char			*get_the_path(char **pathsss, char *cmd);
void			file_opener(t_pipe *p, int i_o);
int				exit_brr(int code);
void			child_process(t_pipe *p, int x);
void			cmd_exec(t_pipe *p, char *cmd);
void			init_struct(t_pipe *p, char **av, int ac, char **env);
void			redirector(t_pipe *p, int x);
int				wait_da_boy(t_pipe *p);
void			handle_exec_error(void);

#endif