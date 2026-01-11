#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "lib.h"

# define STATE_GENERAL 1
# define STATE_DOUBLE_QUOTES 2
# define STATE_SINGLE_QUOTES 3

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RED_IN,
	TOKEN_RED_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
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
void	expand_tokens(t_nodes *tokens, char **envp);
void	free_ast(t_nodes *ast_node);
void	del_token(void *content);

#endif
