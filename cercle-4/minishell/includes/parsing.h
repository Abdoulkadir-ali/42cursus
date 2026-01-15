/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:49:38 by abdoali          ###   ########.fr       */
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
	int				expanded;
}					t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	t_nodes			*left;
	t_nodes			*right;
	int				is_quoted;
}					t_ast;

typedef struct s_exp_input
{
	const char		*str;
	char			**envp;
	int				exit_code;
}					t_exp_input;

typedef struct s_exp_state
{
	int				*i;
	int				*qt;
	int				*wd_quoted;
	char			**curr;
	char			**res;
}					t_exp_state;

typedef struct s_exp_lists
{
	t_nodes			**head;
	t_nodes			**tail;
}					t_exp_lists;

typedef struct s_exp_ctx
{
	t_exp_input		input;
	t_exp_state		state;
	t_exp_lists		lists;
}					t_exp_ctx;

typedef struct s_locals
{
	t_nodes			*head;
	t_nodes			*tail;
	char			*curr;
	int				i;
	int				qt[2];
	int				wd_quoted;
}					t_locals;

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

t_nodes				*process_redirections(t_nodes *cmd_node, t_nodes *tokens);
int					process_matches_or_literal(t_expand_tokens_args *ctx);
t_nodes				*create_node(t_token_type type, char **args, t_nodes *left,
						t_nodes *right);
void				dump_tokens_list(t_nodes *head, const char *stage);
void				add_token_node(t_nodes **head, t_nodes **tail, char *val,
						int quoted);
t_nodes				*tokenizer(char *str);
t_nodes				*ast_builder(t_nodes *tokens);
void				expand_tokens(t_nodes **tokens, char **envp,
						int last_exit_code);
char				*expand_string(char *str, char **envp, int exit_code);
char				*expand_heredoc(char *str, char **envp, int exit_code);
char				*get_env_value(char *var_name, char **envp);
int					is_var_char(char c);
char				*handle_dollar(char *str, int *i, char **envp,
						int exit_code);
void				append_chunk(char **res, char *chunk);
t_nodes				*expand_and_split(char *str, char **envp, int exit_code);
int					check_syntax(t_nodes *tokens);
t_nodes				*expand_wildcard(char *pattern);
t_nodes				*collect_matches(DIR *dir, char *pattern);
int					ft_set_env(char *key, char *value, char ***envp);
char				**expand_wildcards(char **args);
void				free_ast(t_nodes *ast_node);
void				del_token(void *content);
void				append_node(t_nodes **head, t_nodes **tail, t_nodes *node);
int					is_prev_heredoc(t_nodes *prev);
void				apply_tilde_expansion(t_token *tok, char **envp);
t_nodes				*create_token_node_from_match(char *match);
t_nodes				*create_cmd_node(t_nodes *tokens);
int					scan_unquoted(const char *s);
int					scan_quoted(const char *s, char quote);
int					is_wildcard(const char *str);
int					is_redirection(t_token_type type);
int					print_syntax_error(char *token);
int					syntax_handle_lparen(t_token *tok, t_token *nxt,
						int *depth);
int					syntax_handle_rparen(t_token *tok, t_token *nxt,
						int *depth);
int					syntax_handle_pipe_and_logic(t_token *tok, t_token *nxt);
int					syntax_handle_semicolon(t_token *tok, t_token *nxt);
int					syntax_handle_redirection(t_token *tok, t_token *nxt);
void				process_val_split(char *val, t_exp_ctx *ctx);
int					handle_quote_split(t_exp_ctx *ctx);
int					handle_backslash_split(t_exp_ctx *ctx);
int					handle_dollar_split(t_exp_ctx *ctx);
int					handle_pipe(char **str, t_token *token);
int					handle_paren(char **str, t_token *token, int left);
int					handle_ampersand(char **str, t_token *token);
int					handle_red_in(char **str, t_token *token);
int					handle_red_out(char **str, t_token *token);
int					handle_semicolon(char **str, t_token *token);
t_token				*handle_separator(char **str);
int					match_loop(char **pattern, char **str, char **star,
						char **str_start);
t_token				*handle_word(char **str);

#endif
