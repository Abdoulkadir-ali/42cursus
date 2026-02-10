/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 04:11:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// PACKAGE
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

// CUSTOM
# include "lib.h"
# include "libft.h"
# include "state.h"

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
	TOKEN_HERESTR,
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
	struct s_ast	*left;
	struct s_ast	*right;
	int				is_quoted;
}					t_ast;

typedef struct s_exp_input
{
	const char		*str;
	int				pos;
	char			**env;
	int				status;
}					t_exp_input;

typedef struct s_exp_state
{
	int				in_s_quote;
	int				in_d_quote;
	int				has_quotes;
}					t_exp_state;

typedef struct s_exp_output
{
	char			*str;
	char			*word;
	t_nodes			*head;
	t_nodes			*tail;
}					t_exp_output;

typedef struct s_expansion
{
	t_exp_input		input;
	t_exp_state		state;
	t_exp_output	output;
}					t_expansion;

typedef struct s_dollar_peek
{
	int				idx;
	char			next;
}					t_dollar_peek;

typedef struct s_token_expansion
{
	t_nodes			*head;
	t_nodes			*tail;
	t_nodes			*prev;
}					t_token_expansion;

t_ast				*process_redirections(t_ast *cmd_node, t_nodes *tokens);
int					process_matches_or_literal(t_token_expansion *ctx,
						t_nodes *matches, t_token *exp_tok, t_nodes *exp_curr);
t_ast				*create_node(t_token_type type, char **args, t_ast *left,
						t_ast *right);
void				dump_tokens_list(t_nodes *head, const char *stage);
void				add_token_node(t_nodes **head, t_nodes **tail, char *val,
						int quoted);
t_nodes				*tokenizer(char *str);
t_ast				*ast_builder(t_nodes *tokens);
void				expand_tokens(t_nodes **tokens, char **env, int status);
char				*expand_string(char *str, char **env, int status);
char				*expand_heredoc(char *str, char **env, int status);
char				*get_env_value(char *var_name, char **envp);
char				*handle_dollar(char *str, int *i, char **envp,
						int exit_code);
void				append_chunk(char **res, char *chunk);
t_nodes				*expand_and_split(char *str, char **envp, int exit_code);
int					check_syntax(t_nodes *tokens);
t_nodes				*expand_wildcard(char *pattern);
t_nodes				*collect_matches(DIR *dir, char *pattern);
int					ft_set_env(char *key, char *value, t_shell_state *state);
char				**expand_wildcards(char **args);
void				free_ast(t_ast *ast_node);
void				del_token(void *content);
void				append_node(t_nodes **head, t_nodes **tail, t_nodes *node);
int					is_prev_heredoc(t_nodes *prev);
void				apply_tilde_expansion(t_token *tok, char **envp);
t_nodes				*create_token_node_from_match(char *match);
t_ast				*create_cmd_node(t_nodes *tokens);
t_ast				*handle_subshell(t_nodes *tokens);
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
int					is_exp_target(char c);
void				perform_expansion(t_exp_input *in, t_exp_state *st,
						t_exp_output *out);
void				push_literal_dollar(t_exp_input *in, t_exp_output *out,
						int idx);
void				process_val_split(char *val, t_exp_output *out);
int					handle_quote_split(t_exp_input *in, t_exp_state *st,
						t_exp_output *out);
int					handle_backslash_split(t_exp_input *in, t_exp_state *st,
						t_exp_output *out);
int					handle_dollar_split(t_exp_input *in, t_exp_state *st,
						t_exp_output *out);
void				exp_push_char(t_exp_output *out, char c);
void				exp_push_str(t_exp_output *out, char *s);
int					expand_to_string(t_exp_input *in, t_exp_state *st,
						t_exp_output *out, t_dollar_peek *peek);
int					expand_to_tokens(t_exp_input *in, t_exp_state *st,
						t_exp_output *out, t_dollar_peek *peek);
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
int					match_pattern(char *pattern, char *str);
int					should_skip_entry(struct dirent *entry, char *pattern);
void				try_add_match(t_nodes **files, struct dirent *entry,
						int *match_count);
char				*prepare_pattern(char *pattern, int *require_dir);
int					check_entry(struct dirent *entry, char *pat_copy,
						int require_dir);
t_nodes				*process_directory(DIR *dir, char *pat_copy,
						int require_dir);
void				sort_list(t_nodes **list);

#endif
