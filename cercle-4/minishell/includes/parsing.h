/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:48:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// PACKAGE
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// CUSTOM
# include "lib.h"
# include "libft.h"

# define STATE_GENERAL 1
# define STATE_DOUBLE_QUOTES 2
# define STATE_SINGLE_QUOTES 3

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SUBSHELL,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_SEMICOLON
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	int expanded; // 1 if this token was produced by expansion/splitting
}					t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	t_nodes			*left;
	t_nodes			*right;
}					t_ast;

typedef struct s_expand_tokens_args
{
	t_nodes			*new_head;
	t_nodes			*new_tail;
	t_nodes			*curr;
	t_nodes			*next_node;
	t_token			*tok;
	t_nodes			*prev;
	t_nodes			*expanded_list;
	t_nodes			*exp_curr;
	t_nodes			*exp_next;
	t_token			*exp_tok;
	t_nodes			*matches;
}					t_expand_tokens_args;

typedef struct s_exp_ctx
{
	const char		*str;
	int				*i;
	int				*qt;
	int				*wd_quoted;
	char			**curr;
	t_nodes			**head;
	t_nodes			**tail;
	char			**envp;
	int				exit_code;
	char			**res;
}					t_exp_ctx;

/* Prototypes for internal helpers */
t_nodes				*process_redirections(t_nodes *cmd_node, t_nodes *tokens);
int					process_matches_or_literal(t_expand_tokens_args *ctx);
/* Shared helpers implemented in parsing submodules */
t_nodes				*create_node(t_token_type type, char **args, t_nodes *left,
						t_nodes *right);
void				dump_tokens_list(t_nodes *head, const char *stage);
void				add_token_node(t_nodes **head, t_nodes **tail, char *val,
						int quoted);

/* Core parsing API */
t_nodes				*tokenizer(char *str);
t_nodes				*ast_builder(t_nodes *tokens);
void				expand_tokens(t_nodes **tokens, char **envp,
						int last_exit_code);
char				*expand_string(char *str, char **envp, int exit_code);
char				*expand_heredoc(char *str, char **envp, int exit_code);
/* env expansion helpers (split across files) */
char				*get_env_value(char *var_name, char **envp);
int					is_var_char(char c);
char				*handle_dollar(char *str, int *i, char **envp,
						int exit_code);
void				append_chunk(char **res, char *chunk);
t_nodes				*expand_and_split(char *str, char **envp, int exit_code);
int					check_syntax(t_nodes *tokens);
t_nodes				*expand_wildcard(char *pattern);
int					ft_set_env(char *key, char *value, char ***envp);
char				**expand_wildcards(char **args);
void				free_ast(t_nodes *ast_node);
void				del_token(void *content);
void				append_node(t_nodes **head, t_nodes **tail, t_nodes *node);
int					is_prev_heredoc(t_nodes *prev);
void				apply_tilde_expansion(t_token *tok, char **envp);
t_nodes				*create_token_node_from_match(char *match);
t_nodes				*create_cmd_node(t_nodes *tokens);

#endif
