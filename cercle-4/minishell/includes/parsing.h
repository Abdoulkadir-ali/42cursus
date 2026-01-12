#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "lib.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	int			expanded; // 1 if this token was produced by expansion/splitting
}	t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	t_nodes			*left;
	t_nodes			*right;
}	t_ast;

t_nodes	*tokenizer(char *str);
t_nodes	*ast_builder(t_nodes *tokens);
void	expand_tokens(t_nodes **tokens, char **envp, int last_exit_code);
char	*expand_string(char *str, char **envp, int exit_code);
char	*expand_heredoc(char *str, char **envp, int exit_code);
int		check_syntax(t_nodes *tokens);
t_nodes	*expand_wildcard(char *pattern);
int		is_wildcard(const char *str);
char	**expand_wildcards(char **args);
void	free_ast(t_nodes *ast_node);
void	del_token(void *content);

#endif
