/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:07:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/09 20:07:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef enum e_token_type {
    TOKEN_WORD,    // ls, -l
    TOKEN_PIPE,    // |
    TOKEN_RED_IN,  // <
    TOKEN_RED_OUT  // >
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type     type;
    struct s_token  *next;
} t_token;

typedef struct s_ast {
    t_token_type    type;      // PIPE or WORD
    char            **args;    // NULL unless type is WORD
    struct s_ast    *left;     // Left side of pipe
    struct s_ast    *right;    // Right side of pipe
} t_ast;

