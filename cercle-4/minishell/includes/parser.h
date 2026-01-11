/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:07:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:27:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "libft.h"

# define STATE_GENERAL 1
# define STATE_DOUBLE_QUOTES 2
# define STATE_SINGLE_QUOTES 3

typedef enum e_token_type
{
	TOKEN_WORD,   // ls, -l
	TOKEN_PIPE,   // |
	TOKEN_RED_IN, // <
	TOKEN_RED_OUT // >
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	t_nodes			*left;
	t_nodes			*right;
}					t_ast;

t_nodes				*tokenizer(char *str);
t_nodes				*ast_builder(t_nodes *tokens);
void				expand_tokens(t_nodes *tokens, char **envp);
void				free_ast(t_nodes *ast_node);

void				del_token(void *content);

int					ft_strmatch(char *s1, char *s2, int (*match)(char *,
							char *));
int					str_any(char *s1, char *s2);

#endif
